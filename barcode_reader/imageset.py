import cv2
import errno
from json import load
import logging
from cv2 import INTER_LINEAR
import numpy as np
import os

__all__ = ["ImageSet"]


class ImageSetItem:
    _id: int
    _image_abspath: str
    _image_content: str
    _image: np.ndarray

    def __init__(self, id, abspath, content) -> None:
        self._id = id
        self._image_abspath = abspath
        self._image_content = content
        self._image = None

    def load_image(self, force_refresh=False) -> None:
        if self._image is None or force_refresh:
            self._image = cv2.imread(self._image_abspath)

    def get_id(self) -> int:
        return self._id

    def get_abspath(self) -> str:
        return self._image_abspath

    def get_content(self) -> str:
        return self._image_content

    def get_image(self) -> np.ndarray:
        self.load_image()
        return self._image.copy()

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}(id={self._id}, image={os.path.basename(self._image_abspath)}, content={self._image_content})"


class ImageSet:
    _items: dict[int, ImageSetItem]

    def __init__(self, path, preload=False, table_path="imageset.json") -> None:
        self._items = dict()
        self.check_dataset(path, table_path)
        if preload:
            self.preload_items_images()

    def check_dataset(self, path, table_path) -> None:
        with open(path + table_path) as fp:
            imageset_data = load(fp)

            imageset_abspath = os.path.join(os.path.abspath(os.path.curdir), path)

            for filename in imageset_data:

                filename_abspath = os.path.join(imageset_abspath, filename)

                if not os.path.isfile(filename_abspath):
                    raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), filename_abspath)

                nb_items = len(self._items)
                self._items[nb_items] = ImageSetItem(nb_items, filename_abspath, imageset_data[filename])

        logging.info(f"Checked {len(self._items)} images from \"{imageset_abspath}\"")

    def preload_items_images(self) -> None:
        for i in self._items:
            self._items[i].load_image()

        logging.info(f"Preloading finished ({len(self._items)} images)")

    def __repr__(self) -> str:
        return f"{self.__class__.__name__}({self._items})"

    def __iter__(self) -> ImageSetItem:  # Iterator, i.e. `for image in imageSet`
        return (v for v in self._items.values())

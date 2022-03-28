from __future__ import annotations
from base64 import decode  # Enables type hinting before full class declaration, for example in Point.distance

import cv2
from math import sqrt
import numpy as np
from pyzbar import pyzbar


class Point2D:
    x: float
    y: float

    def __init__(self, x=0, y=0) -> None:
        self.x = x
        self.y = y

    def get_pos(self) -> tuple[float, float]:
        return (self.x, self.y)

    def distance(self, p: Point2D) -> float:
        return self.vector_to(p).norm()

    def squared_distance(self, p: Point2D) -> float:
        return self.vector_to(p).squared_norm()

    def euclidean_distance(self, p: Point2D) -> float:
        return self.vector_to(p).euclidean_norm()

    def vector_to(self, p: Point2D) -> Vector2D:
        return Vector2D(p.x - self.x, p.y - self.y)

    def __lt__(self, p: Point2D) -> Vector2D:
        """so you can write a>b, which kinda looks like a→b"""
        return self.vector_to(p)

    def __add__(self, v: Vector2D) -> Point2D:
        if not isinstance(v, Vector2D):
            raise TypeError(v)
        return Point2D(self.x + Vector2D.x, self.y + Vector2D.y)

    def __sub__(self, v: Vector2D) -> Vector2D:
        if not isinstance(v, Vector2D):
            raise TypeError(v)
        return self + (-v)

    def __getitem__(self, i: int) -> float:
        if i > 1 or i < 0:
            raise IndexError
        return (self.x if i == 0 else self.y)


class Vector2D:
    x: float
    y: float

    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y

    def __add__(self, v: Vector2D) -> Vector2D:
        return Vector2D(self.x + v.x, self.y + v.y)

    def __sub__(self, v: Vector2D) -> Vector2D:
        return self + (-v)

    def __neg__(self) -> Vector2D:
        return Vector2D(-self.x, -self.y)

    def __div__(self, x: float | int):
        return self * (1/x)

    def __mul__(self, x: float | int):
        return Vector2D(x * self.x, x * self.y)

    def __inv__(self):
        """vector normal"""
        return Vector2D(-self.y, self.x)

    def normal(self):
        return ~self

    def norm(self):
        return sqrt(self.squared_norm())

    def squared_norm(self):
        return self.x ** 2 + self.y ** 2

    def euclidean_norm(self):
        return abs(self.x) + abs(self.y)


class BarcodeDetectorResult:
    _top_left: Point2D
    _width: Vector2D
    _height: Vector2D
    _value: str

    def __init__(self, top_left: Point2D = None, width: Vector2D = None, height: Vector2D = None, value: str = "") -> None:
        self._top_left = top_left
        self._width = width
        self._height = height
        self._value = value


class BarcodeDetector:

    def __init__(self) -> None:
        pass

    def process_image(self, input_image: np.ndarray) -> BarcodeDetectorResult:
        decoded_result = pyzbar.decode(input_image)
        if len(decoded_result) == 0:
            return BarcodeDetectorResult()

        best_quality = 0
        best_barcode = None

        for barcode in decoded_result:
            if barcode.quality > best_quality:
                best_quality = barcode.quality
                data = barcode.data.decode()
                rect = barcode.rect
                best_barcode = BarcodeDetectorResult(Point2D(rect.left, rect.top), Vector2D(
                    rect.width, 0), Vector2D(0, rect.height), data)
        return best_barcode

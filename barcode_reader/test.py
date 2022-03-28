from argparse import ArgumentError
import imageset
import detector
import cv2
import json

import sys

DEFAULT_CONFIG_FILE = "default_config.json"


def usage():
    print(f"Usage: python {sys.argv[0]} [args...]")
    print("--dataset_path=[path] test the detector against a dataset, can be used with --preload")
    print("--video_path=[path] test the detector using a live video feed")
    print("--config=[path] change the config file (default file is default_config.json)")
    print("NOTE: dataset_path and video_path are mutually exclusive")


if __name__ == "__main__":
    str_args = {"--dataset_path": None,
                "--video_path": None,
                "--config": DEFAULT_CONFIG_FILE
                }

    bool_args = []  # Con,tains args like "--preload" with no assigned value

    if len(sys.argv) == 1:  # No args
        usage()
        sys.exit()

    # Arg parsing
    i = 0
    while i < len(sys.argv):
        arg = sys.argv[i]

        is_str_arg = False
        for key in str_args:
            split_arg = arg.split("=", 1)
            if split_arg[0] == key:  # Split --arg=value to ["--arg","value"]
                is_str_arg = True
                if len(split_arg) == 1:
                    raise ArgumentError(None, "No value specified for arg " + key)

                str_args[key] = split_arg[1]
            else:
                bool_args.append(arg)  # For args such as "--preload"

        i += 1

    dataset_path = str_args["--dataset_path"]
    video_path = str_args["--video_path"]
    config_path = str_args["--config"]

    if (dataset_path is None) and (video_path is None):
        usage()
        sys.exit()

    if (dataset_path is not None) and (video_path is not None):
        raise ArgumentError(None, "Cannot both specify a dataset and a video device")

    config = None
    with open(config_path) as fp:
        config = json.load(fp)

    detector = detector.BarcodeDetector()

    # DATASET TEST
    if dataset_path is not None:
        preload = "--preload" in bool_args
        image_set = imageset.ImageSet(dataset_path, preload=preload, table_path=config["imageset"]["table_path"])

        image: imageset.ImageSetItem
        for image in image_set:
            result = detector.process_image(image.get_image())
            result_bool_str = "✅" if result._value == image.get_content() else "🛑"
            print(f"#{image.get_id()}: {result_bool_str} expected {image.get_content()}, got {result._value}")

    # LIVE VIDEO TEST
    if video_path is not None:
        cam = cv2.VideoCapture(video_path)

        while True:
            err, source_img = cam.read()
            detector_result = detector.process_image(source_img)
            dr = detector_result

            if dr._value is not None:

                # Generating rectangle overlay for live feedback
                top_left = dr._top_left
                top_right = dr._top_left + dr._width
                bot_left = dr._top_left + dr._height
                bot_right = dr._top_left + dr._height + dr._width

                cv2.line(source_img, top_left.tuple(), top_right.tuple(), (255, 0, 255), 2)
                cv2.line(source_img, bot_left.tuple(), bot_right.tuple(), (255, 0, 255), 2)
                cv2.line(source_img, top_left.tuple(), bot_left.tuple(), (255, 0, 255), 2)
                cv2.line(source_img, top_right.tuple(), bot_right.tuple(), (255, 0, 255), 2)

                cv2.addText(source_img, detector_result._value, bot_left.tuple(), None, 20, (0, 0, 0), 75)
                cv2.addText(source_img, detector_result._value, bot_left.tuple(), None, 20, (255, 255, 255), 70)

            cv2.imshow("camera", source_img)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

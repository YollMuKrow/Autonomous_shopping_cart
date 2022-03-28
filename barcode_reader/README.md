# Dependencies
 - Python >=3.10 (I used 3.10 but earlier versions might work)
    - OpenCV >= 4.5.5.62 (pip install opencv-python)
    - Numpy >= 1.22.3 (should come with opencv)
    - pyzbar >= 0.1.9 
 - zbar >= 0.23.1-0 (using your package manager, in my case pacman -S zbar)

# Testing
`python test.py` for the full documentation

Quick examples:

 - `python test.py --dataset_path=images` to test the default dataset
 - `python test.py --dataset_path=images --preload` to test the default dataset WITH preloading (could speed up the program)
 - `python test.py --video_path=/dev/video0` to test using the default webcam installedS
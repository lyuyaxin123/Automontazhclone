
rem darknet.exe detector test data/voc.data yolo-voc.cfg yolo-voc.weights 009460.jpg


darknet_no_gpu.exe detector test data/voc.data yolo-voc.cfg yolo-voc.weights -i 0 -thresh 0.2 monitor.jpg


pause
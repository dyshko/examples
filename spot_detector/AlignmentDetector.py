import cv2

def distance(filename):
    """ Calculates the distance from the center of the image
        to the detected white spot on the image
        If no or multiple spots are detected, returns None

        Assumptions:
            - the spot contains the whitest pixel of the image
    """
    # Read image in grayscale
    raw_img = cv2.imread(filename, cv2.IMREAD_GRAYSCALE) 

    if raw_img is None:
        return None

    #next, we use adaptive threshold binary search to detect the threshold value
    #for which we detect exactly one spot

    #threshold bounds, initially set as max and min brightness of the pixels on the image
    upper_bound = raw_img.max()
    lower_bound = raw_img.min()

    #the loop will run at most 8 = log_2(256) times
    while upper_bound > lower_bound + 1:

        #apply threshold to the image
        threshold = (upper_bound + lower_bound)//2
        _ , im = cv2.threshold(raw_img, threshold , 255, cv2.THRESH_BINARY_INV)

        #uncomment the next line to see the image
        #cv2.imshow("thresholded image", im)

        # detect blobs using simple blob detector
        detector = cv2.SimpleBlobDetector_create()
        keypoints = detector.detect(im)

        if len(keypoints) == 1:
            #one spot detected - return the distance
            height, width = im.shape[:2]
            distance = cv2.norm(keypoints[0].pt, (width//2, height//2))
            return distance
        
        elif len(keypoints) > 1:
            #multiple blobs detected - increase threshold
            lower_bound = threshold
            
        else:
            #no blobs detected - decrease threshold
            upper_bound = threshold

    #none or multiple blobs detected 
    return None

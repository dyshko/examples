import AlignmentDetector

def Test(image_name, expected_value):
    """checks if expected_value correspond to the evaluation result"""
    value = AlignmentDetector.distance(image_name)
    passed = False
    if value is None:
        passed = True if expected_value is None else False
    else:
        if expected_value is None:
            passed = False
        else:
            #assume allowed error within 1px range
            passed = abs(value - expected_value) <= 1

    print(("PASSED" if passed else "FAILED") +
          ": {0}, expected: {1}, obtained: {2}".format(image_name, expected_value, value))

test_values = {"spot1.tif":82,
               "spot2.tif":106,
               "spot3.tif":816,
               "no_spot.tif":None,
               "two_spots.tif":None,
               "spot_with_noise.tif":106}

for img_name, expected_value in test_values.items():
    Test(img_name, expected_value)

from src.person import Person
from src.sequencescore import *


def label(persons):
    """
    Classify a person based on it's previous payment history
    The labels are used for the training of the regression model
    :param persons:
    :return:
    """
    threshold = 0.031
    count = {Person.Label.BAD: 0,
             Person.Label.AVERAGE: 0,
             Person.Label.GOOD: 0}
    for p in persons:
        if p.negative_balance_score.evicted:
            p.label = Person.Label.BAD
            count[Person.Label.BAD] += 1
        elif p.negative_balance_score.max_width == 0:
            p.label = Person.Label.GOOD
            count[Person.Label.GOOD] += 1
        elif average_area_over_all_days(p.negative_balance_score) <= threshold:
            p.label = Person.Label.AVERAGE
            count[Person.Label.AVERAGE] += 1
        else:
            p.label = Person.Label.BAD
            count[Person.Label.BAD] += 1
    return count

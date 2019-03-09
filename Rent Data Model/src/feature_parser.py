import operator
from enum import Enum

from src.person import Person
from src.sequencescore import *
from src.transaction import Transaction


class Feature(Enum):
    """
    Features used as input to regression model
    """
    CONTRACTS = 0,
    PAYMENT_METHOD = 1,
    AVG_AREA_ACT = 2,
    AVG_AREA_ALL = 3,
    AVG_AREA_CYC = 4,
    AVG_ACT_LENGTH = 5,
    RATIO_ACTIVE = 6,
    MAX_ACTIVE = 7,
    MAX_AREA = 8,
    AGE = 9


def save_data(persons):
    """
    Save the processed training data to file
    @TODO use pickle instead of a file
    :param persons:
    :return:
    """
    with open("./data/features_labels.csv", "w") as f:
        f.write("contracts,payment_method,avg_area_act,avg_area_all,avg_area_cyc,avg_act_length,ratio_active,"
                "max_active,max_area,age,label\n")
        keys = [Feature.CONTRACTS, Feature.PAYMENT_METHOD, Feature.AVG_AREA_ACT, Feature.AVG_AREA_ALL,
                Feature.AVG_AREA_CYC, Feature.AVG_ACT_LENGTH, Feature.RATIO_ACTIVE, Feature.MAX_ACTIVE,
                Feature.MAX_AREA, Feature.AGE]
        for p in persons:
            # if p.label == Person.Label.GOOD:
            #    continue
            base_f = collect_features(p)
            for feat in base_f:
                vals = [feat[key] for key in keys]
                f.write(",".join([str(x) for x in vals]))
                f.write("," + str(p.label) + "\n")


def collect_features(person: Person):
    """
    for a given person get the least of the features is provides
    for the regression
    :param person:
    :return:
    """
    base_f = []
    for c in person.contracts:
        base_f += collect_base_features(c.negative_sequence)

    contracts_num = len(person.contracts)
    now = datetime.date(2019, 1, 31)
    age = int(abs((now - person.dob).days) / 365.25)

    typs = {Transaction.Type.CASH: 0, Transaction.Type.DIRECT_DEBIT: 0, Transaction.Type.BANK_TRANSFER: 0}
    for c in person.contracts:
        for t in c.transactions_obj:
            typs[t.method] += 1
    method = max(typs.items(), key=operator.itemgetter(1))[0]

    for f in base_f:
        f[Feature.AGE] = age
        f[Feature.PAYMENT_METHOD] = method
        f[Feature.CONTRACTS] = contracts_num

    return base_f


def collect_base_features(seq):
    """
    util function to get part of the features (see the code)
    :param seq:
    :return:
    """
    days = sorted(seq.keys())
    start = days[0]
    end = days[-1]
    window = 9

    base_features = []

    i = 0
    while True:
        first_day = add_months(start, i * window)
        last_day = add_months(start, i * window + window)
        if last_day >= end:
            break
        i += 1

        subseq = {}
        for d in days:
            if first_day <= d <= last_day:
                subseq[d] = seq[d]

        subseq_score = SequenceScore(subseq)

        feature = dict()
        feature[Feature.AVG_AREA_ACT] = average_area_over_active_days(subseq_score)
        feature[Feature.AVG_AREA_ALL] = average_area_over_all_days(subseq_score)
        feature[Feature.AVG_AREA_CYC] = avg_area_per_cycle(subseq_score)
        feature[Feature.AVG_ACT_LENGTH] = average_active_length(subseq_score)
        feature[Feature.RATIO_ACTIVE] = ratio_of_active(subseq_score)
        feature[Feature.MAX_ACTIVE] = max_active_value(subseq_score)
        feature[Feature.MAX_AREA] = max_area(subseq_score)

        base_features.append(feature)

    return base_features

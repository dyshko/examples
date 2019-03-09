from src.datareader import *
from src.feature_parser import *
from src.labeler import *
from src.visualize import *


def display_rent_duration_ratios(people):
    """
    util function to display duration chart
    :param people:
    :return:
    """

    def with_duration_leq(max_dur):
        total = 0
        for p in people:
            if p.rent_months <= max_dur:
                total += 1
        return 100 * total / len(people)

    print("% of people with rent duration not greater than")
    print("3 months", with_duration_leq(3))
    print("6 months", with_duration_leq(6))
    print("12 months", with_duration_leq(12))
    print("18 months", with_duration_leq(18))
    print("24 months", with_duration_leq(24))
    show_rent_duration_hist(people)


# read the data from CSV files
# @TODO use pandas dataframes
persons, contracts, faulty_transactions, empty_contracts = read_data("./data/contracts.csv",
                                                                     "./data/transactions.csv")
max_trans = 0
total_trans = 0
max_contracts = 0

# get number of evicted persons
evicted_delays = []
non_evicted_persons = []
for p in persons:
    total_trans += len(p.payments)
    max_trans = max(max_trans, len(p.payments))
    max_contracts = max(max_contracts, len(p.contracts))
    if p.negative_balance_score.evicted:
        evicted_delays.append(p.negative_balance_score.evicted_days)
    else:
        non_evicted_persons.append(p)

# number of contracts statistic
persons_with_one_contract = [p for p in persons if len(p.contracts) == 1]
persons_with_more_contracts = [p for p in persons if len(p.contracts) > 1]
persons_with_more_contracts_avg = sum([len(p.contracts) for p in persons_with_more_contracts]) \
                                  / len(persons_with_more_contracts)

print("Persons: ", len(persons))
print("Persons (not evicted): ", len(persons_with_one_contract))
print("Average contracts for multi-contract person", persons_with_more_contracts_avg)
print("Persons 1 contract:", len(persons_with_more_contracts))
print("Contracts with transactions: ", len(contracts) - len(empty_contracts))
print("Contracts with no transactions", len(empty_contracts))
print("Total transactions with contracts", total_trans - len(faulty_transactions))
print("Transactions with no contracts", len(faulty_transactions))

# persons with one payment method
one_payment = []
for p in persons:
    methods = {}
    for c in p.contracts:
        for t in c.transactions_obj:
            if t.method not in methods:
                methods[t.method] = True
    if len(methods.keys()) == 1:
        one_payment.append(p)

print("Persons with one payment method", len(one_payment))
print("Persons with multiple payment methods", len(persons) - len(one_payment))

visualize_delays_eviction(evicted_delays)
show_avg_debt_hist(persons)
persons_negative_score_hist(persons)

contracts_with_deposit = []
for c in contracts:
    if c.with_deposit:
        contracts_with_deposit.append(c)
print("Contracts with deposit returns", len(contracts_with_deposit))

display_rent_duration_ratios(non_evicted_persons)

print("Persons of each type:")
count = label(persons)
for lvl in count:
    print("   ", lvl, count[lvl])

save_data(persons)

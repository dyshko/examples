from src.person import Person
from src.sequencescore import SequenceScore
from src.utils import *


class Contract:
    id: int
    postcode: str
    rent: float
    start: datetime
    end: datetime

    person: Person
    transactions_obj: list
    payments: dict

    def __init__(self, data_string):

        data_list = data_string.split(",")

        self.id = None
        self.person = None
        self.postcode = None
        self.rent = None
        self.start = None
        self.end = None
        self.payments = {}
        self.months = 0
        self.deductions = {}
        self.transactions_obj = []
        self.negative_balance_score = SequenceScore()
        self.positive_balance_score = SequenceScore()
        self.with_deposit = False
        self.negative_sequence = {}

        if len(data_list) != 8:
            return

        self.id = int(data_list[0])
        self.person = Person(data_list[1], data_list[2], data_list[3])
        self.postcode = data_list[4]
        self.rent = float(data_list[5])
        self.start = str_to_date(data_list[6])
        self.end = str_to_date(data_list[7])

    def attach_transaction(self, transaction):
        if transaction.date < self.start or (self.end is not None and transaction.date > self.end):
            print("Transaction out of range")
            return
        self.transactions_obj.append(transaction)
        if transaction.date not in self.payments:
            self.payments[transaction.date] = 0
        self.payments[transaction.date] += transaction.amount

    def valid(self):
        return self.id is not None and \
               self.person is not None and \
               self.rent is not None and \
               self.start is not None

    def process_transactions(self):
        # select end date (if not specified)
        dates = sorted(self.payments.keys())

        i = 0
        while add_months(self.start, i) <= dates[0]:
            i += 1
        date_start = add_months(self.start, i - 1)
        date_end = dates[-1]

        # rent as a negative transaction
        for i in range(months_between(date_start, date_end)):
            rent_date = add_months(date_start, i)
            self.deductions[rent_date] = -self.rent

        # combine together
        all_transactions = dict(self.payments)
        for date in self.deductions:
            if date not in all_transactions:
                all_transactions[date] = 0
            all_transactions[date] += self.deductions[date]

        all_dates = sorted(all_transactions.keys())

        if len(all_dates) > 0:
            self.months = months_between(all_dates[0], all_dates[-1])

        balance = 0
        negative_sequence = {}
        positive_sequence = {}
        for date in all_dates:
            value = all_transactions[date]
            balance += value

            if balance < 0:
                negative_sequence[date] = -balance / self.rent
                positive_sequence[date] = 0
            elif balance > 0:
                negative_sequence[date] = 0
                positive_sequence[date] = balance / self.rent
            else:
                negative_sequence[date] = 0
                positive_sequence[date] = 0

        self.negative_sequence = negative_sequence
        self.negative_balance_score = SequenceScore(negative_sequence)
        self.with_deposit = self.negative_balance_score.deposit_return
        if self.with_deposit:
            del self.negative_sequence[max(negative_sequence.keys())]
        # self.positive_balance_score = SequenceScore(positive_sequence)

from enum import Enum

from src.sequencescore import SequenceScore
from src.utils import *


class Person:
    """
    The class representing the Person/tenant
    contains details/contracts/payments/evictions references
    as well as some labeling data.
    """

    first_name: str
    last_name: str
    dob: datetime
    contracts: list

    class Label(Enum):
        GOOD = 0,
        AVERAGE = 1,
        BAD = 2

    def __init__(self, fname, lname, dob):
        self.first_name = fname
        self.last_name = lname
        self.dob = str_to_date(dob)
        self.dob_str = dob
        self.contracts = []
        self.payments = []
        self.rent_months = 0
        self.negative_balance_score = SequenceScore()
        self.label = None

    def __str__(self):
        return self.first_name + " " + self.last_name + " " + self.dob_str

    def attach_contract(self, contract):
        """
        add a contract to the list while processing it
        :param contract:
        :return:
        """
        self.contracts.append(contract)
        self.negative_balance_score = self.negative_balance_score.combine(contract.negative_balance_score)
        self.rent_months += contract.months
        for trans in contract.payments:
            self.payments.append(trans)

    def valid_contracts(self):
        """
        :return: true if no contradictory data found
        """
        date_list = {}
        for c in self.contracts:
            if c.start not in date_list:
                date_list[c.start] = 0
            date_list[c.start] += 1
            if c.end is not None:
                if c.end not in date_list:
                    date_list[c.end] = 0
                date_list[c.end] -= 1
        current_contracts = 0
        for date in sorted(date_list.keys()):
            val = date_list[date]
            if val > 1 or val < -1:
                return False
            current_contracts += val
            if current_contracts < 0 or current_contracts > 1:
                return False
        return True

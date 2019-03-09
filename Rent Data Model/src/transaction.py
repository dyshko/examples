from enum import Enum

from src.contract import Contract
from src.utils import *


class Transaction:
    """
    Class representing a payment
    """

    class Type(Enum):
        CASH = 1
        DIRECT_DEBIT = 2
        BANK_TRANSFER = 3

    contract_id: int
    contract: Contract
    date: datetime
    amount: float
    method: Type

    @classmethod
    def str_to_type(cls, type_str):
        if type_str == "CASH":
            return Transaction.Type.CASH
        elif type_str == "DIRECT_DEBIT":
            return Transaction.Type.DIRECT_DEBIT
        elif type_str == "BANK_TRANSFER":
            return Transaction.Type.BANK_TRANSFER
        else:
            return None

    def __init__(self, data_string):

        data_list = data_string.split(",")
        amount_str = data_list[2]
        self.contract_id = int(data_list[0])
        self.contract = None
        self.date = str_to_date(data_list[1])
        self.amount = float(amount_str) if amount_str != "" else None
        self.method = self.str_to_type(data_list[3])

    def valid(self):
        return self.amount is not None and self.method is not None and self.date is not None

from src.transaction import *


def read_data(contract_filename, transactions_filename):
    """
    read the plain data from the contracts/transactions files
    :param contract_filename:
    :param transactions_filename:
    :return:
    """
    contracts_dic = {}
    persons_dic = {}
    faulty_transactions = []
    empty_contracts = []
    valid_contracts = []

    # Read contracts
    for line in read_csv(contract_filename):
        contract = Contract(line.rstrip('\n'))
        if contract.id in contracts_dic:
            print("Contract id already exists", contract.id)
            continue
        if contract.valid():
            contracts_dic[contract.id] = contract
        else:
            print("Invalid contract", contract.id)
            continue

    # read transactions and attach to contracts
    for line in read_csv(transactions_filename):
        transaction = Transaction(line.rstrip('\n'))
        if transaction.valid() and transaction.contract_id in contracts_dic:
            contract = contracts_dic[transaction.contract_id]
            transaction.contract = contract
            contract.attach_transaction(transaction)
        else:
            faulty_transactions.append(transaction)

    # attach contracts to persons
    for contract in contracts_dic.values():
        if contract.payments == {}:
            empty_contracts.append(contract)
        else:
            valid_contracts.append(contract)
            contract.process_transactions()
            person_str = str(contract.person)
            if person_str not in persons_dic:
                persons_dic[person_str] = contract.person
            persons_dic[person_str].attach_contract(contract)
            contract.person = persons_dic[person_str]

    valid_persons = []
    for _, p in persons_dic.items():
        if not p.valid_contracts():
            print("Invalid person: intersecting contracts")
        else:
            valid_persons.append(p)

    return valid_persons, valid_contracts, faulty_transactions, empty_contracts

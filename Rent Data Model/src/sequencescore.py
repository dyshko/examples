from src.utils import *


def average_area_over_active_days(seq):
    if seq.sum_width > 0:
        return seq.sum_area / seq.sum_width
    return 0


def average_area_over_all_days(seq):
    if seq.sum_width > 0:
        return seq.sum_area / seq.total_width
    return 0


def avg_area_per_cycle(seq):
    if seq.num_cycles > 0:
        return seq.sum_area / seq.num_cycles
    return 0


def average_active_length(seq):
    if seq.num_cycles:
        return seq.sum_width / seq.num_cycles
    return 0


def ratio_of_active(seq):
    if seq.sum_width:
        return seq.sum_width / seq.total_width
    return 0


def max_active_value(seq):
    return seq.max_value


def max_area(seq):
    return seq.max_area


def longest_width(seq):
    return seq.max_width


class SequenceScore:
    """
    a set of values associated with the sequence of numbers
    """

    def __init__(self, sequence={}):

        self.max_value = 0
        self.sum_area = 0
        self.max_width = 0
        self.sum_width = 0
        self.max_area = 0
        self.total_width = 0
        self.num_cycles = 0
        self.deposit_return = False
        self.evicted = False
        self.evicted_days = 0

        if sequence != {}:
            self.from_sequence(sequence)

    def combine(self, other):
        """
        cummulative scores
        :param other:
        :return:
        """
        res = SequenceScore()

        res.sum_area = self.sum_area + other.sum_area
        res.max_value = max(self.max_value, other.max_value)
        res.max_width = max(self.max_width, other.max_width)
        res.sum_width = self.sum_width + other.sum_width
        res.max_area = self.max_area + other.max_area
        res.total_width = self.total_width + other.total_width
        res.num_cycles = self.num_cycles + other.num_cycles

        res.evicted = self.evicted or other.evicted
        res.evicted_days = max(self.evicted_days, other.evicted_days)

        return res

    def from_sequence(self, sequence):
        """
        evaluates scores from a number sequence
        :param sequence:
        :return:
        """
        first_date = min(sequence.keys())
        last_date = max(sequence.keys())
        self.total_width = (last_date - first_date).days

        cycle_widths = []
        cycle_areas = []

        # to close the last cycle
        aux_date = last_date + datetime.timedelta(days=1)
        sequence[aux_date] = 0
        all_days = sorted(sequence.keys())

        last_cycle_start = first_date
        previous_value = 0
        values = []
        cycle_area = 0
        previous_date = first_date
        for date in all_days:
            value = sequence[date]

            if value > 0 and previous_value == 0:
                last_cycle_start = date
                cycle_area = 0
            cycle_area += previous_value * (date - previous_date).days
            if value == 0 and previous_value > 0:  # cycle ended
                cycle_width = (date - last_cycle_start).days

                # check last month deposit return
                deposit_return = cycle_width == 1 and date == aux_date and previous_value == 2.0
                if deposit_return:
                    self.deposit_return = True
                    del values[-1]
                    break

                cycle_widths.append(cycle_width)
                cycle_areas.append(cycle_area)

                # check evicted (no deposit - already checked)
                if date == aux_date and cycle_width > 1:  # at least 2 days (of non payment)
                    if not self.evicted:  # first time
                        self.evicted_days = cycle_width
                    self.evicted = True

            previous_value = value
            previous_date = date
            values.append(value)

        self.max_value = max(values)
        self.num_cycles = len(cycle_widths)
        if cycle_widths:
            self.max_width = max(cycle_widths)
            self.max_area = max(cycle_areas)
            self.sum_area = sum(cycle_areas)
            self.sum_width = sum(cycle_widths)

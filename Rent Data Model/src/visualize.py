import matplotlib.pyplot as plt

from src.sequencescore import *


def plot_score_hist(people, func, caption, bins=100):
    vals = [func(p.negative_balance_score) for p in people]
    nonzero_vals = [x for x in vals if x != 0]
    plt.hist(nonzero_vals, bins=bins)
    plt.ylabel('People')
    plt.title(caption)


def visualize_delays_eviction(vals):
    plt.hist(vals, bins=50)
    plt.ylabel('Evicted tenants')
    plt.title("Debt days prior to eviction")
    plt.show()


def show_avg_debt_hist(persons):
    plot_score_hist(persons, average_area_over_all_days, "Avg debt area per day", 300)
    plt.show()


def persons_negative_score_hist(persons):
    plt.subplot(3, 2, 1)
    plot_score_hist(persons, max_area, "Max debt power")
    plt.subplot(3, 2, 2)
    plot_score_hist(persons, average_active_length, "Avg time in debt (days)")
    plt.subplot(3, 2, 3)
    plot_score_hist(persons, average_area_over_all_days, "Avg debt per day")
    plt.subplot(3, 2, 4)
    plot_score_hist(persons, longest_width, "Longest debt (days)")
    plt.subplot(3, 2, 5)
    plot_score_hist(persons, ratio_of_active, "Ratio of days in debt")
    plt.subplot(3, 2, 6)
    plot_score_hist(persons, max_active_value, "Max debt")

    plt.show()


def show_rent_duration_hist(persons):
    vals = [p.rent_months for p in persons]
    plt.hist(vals, bins=50)
    plt.ylabel('People')
    plt.title('Total rent duration (in months)')
    plt.show()

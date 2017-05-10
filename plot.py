import pandas as pd
import matplotlib.pyplot as plt

pd.read_csv('diffs.csv').plot(kind='bar')

plt.legend(loc='lower right')
plt.show()

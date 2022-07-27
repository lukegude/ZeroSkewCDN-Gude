import matplotlib.pyplot as plt
import numpy as np

def plot_clock():
    ax.plot([0, 3.875], [0, 0], linewidth=1.000000, color='r')
    ax.plot([3.875, 3.875], [0, 5.2], linewidth=1.000000, color='b')
    ax.plot([3.875, 1.25], [5.2, 5.2], linewidth=1.000000, color='r')
    ax.plot([1.25, 1.25], [5.2, 1.9], linewidth=1.000000, color='b')
    ax.plot([3.875, 6.5], [5.2, 5.2], linewidth=1.000000, color='r')
    ax.plot([6.5, 6.5], [5.2, 8.5], linewidth=1.000000, color='b')
    ax.plot([1.25, 1], [1.9, 1.9], linewidth=1.000000, color='r')
    ax.plot([1, 1], [1.9, 2], linewidth=1.000000, color='b')
    ax.plot([1.25, 1.5], [1.9, 1.9], linewidth=1.000000, color='r')
    ax.plot([1.5, 1.5], [1.9, 1.8], linewidth=1.000000, color='b')
    ax.plot([6.5, 5], [8.5, 8.5], linewidth=1.000000, color='r')
    ax.plot([5, 5], [8.5, 8], linewidth=1.000000, color='b')
    ax.plot([6.5, 8], [8.5, 8.5], linewidth=1.000000, color='r')
    ax.plot([8, 8], [8.5, 9], linewidth=1.000000, color='b')

    ax.text(0, 0, 'XX')
    ax.text(3.875, 5.2, 'XX')
    ax.text(1.25, 1.9, 'XX')
    ax.text(1, 2, 'XX')
    ax.text(1.5, 1.8, 'XX')
    ax.text(6.5, 8.5, 'XX')
    ax.text(5, 8, 'XX')
    ax.text(8, 9, 'XX')


fig = plt.figure()
ax = fig.add_subplot(111)
showlabels = True
# plot_temp()
# # plot_blockages()
plot_clock()
# plot_lc_tanks()
# plot_node_labels()
# plot_seg_labels()
# plot_buff_labels()
# plot_lc_labels()
ax.axis([-5, 12, -5, 12])
plt.show()


fig = plt.figure()
ax = fig.add_subplot(111)
showlabels = True
# plot_temp()
# # plot_blockages()
plot_clock()
# plot_lc_tanks()
# plot_node_labels()
# plot_seg_labels()
# plot_buff_labels()
# plot_lc_labels()
ax.axis([-5, 12, -5, 12])
plt.show()

import matplotlib.pyplot as plt
import numpy as np

def plot_clusters(file_name):
    # Read the file and extract points and their cluster index
    points = []
    with open(file_name, 'r') as f:
        for line in f:
            x, y, index = line.strip().split()
            points.append((float(x), float(y), int(index)))

    # Separate points into clusters
    clusters = {}
    centers = []
    for x, y, index in points:
        if index == -1:
            centers.append((x, y))
        else:
            if index not in clusters:
                clusters[index] = []
            clusters[index].append((x, y))

    # Plotting the clusters
    for cluster_index, cluster_points in clusters.items():
        cluster_points = np.array(cluster_points)
        plt.scatter(cluster_points[:, 0], cluster_points[:, 1]), #label=f'Cluster {cluster_index}')

    # Plotting the centers
    centers = np.array(centers)
    if len(centers) > 0:
        plt.scatter(centers[:, 0], centers[:, 1], color='black', marker='X', s=150, label='Centers')

    plt.legend()
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Cluster Visualization')
    plt.grid(True)
    plt.savefig("Clusters_Visualization.png")
    plt.show()

plot_clusters('clusters_rep.dat')

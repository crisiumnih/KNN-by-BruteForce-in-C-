# KNN-by-BruteForce-in-C++
Implemented K-Nearest Neighbors (KNN) algorithm by BruteForce for classification using C++.


### Code Structure

- **`KNN.cpp` **: Implementation of the KNN class, which encapsulates the functionality of the algorithm. The class includes methods for reading CSV data, normalizing features, calculating distances, and making predictions.
- **`DataPoint` struct**: Defines the structure of a data point, including feature vectors and labels.
- **`distformula` function**: Computes the distance between two vectors.
- **`normalization` function**: Normalizes a feature vector.

### Usage

To use the KNN algorithm for your own datasets, follow these steps:

1. Replace the sample dataset in `main.cpp` with your own data.
2. Ensure the CSV file is formatted correctly with features and labels.
3. Customize the algorithm parameters in the `algot` method in `KNN.cpp` if needed.
4. Compile and run the program to see classification predictions.

### Future Enhancements

This code represents a basic implementation of the KNN algorithm. Future updates may include:

- Optimization for larger datasets.
- Handling of varying feature dimensions.
- Support for different distance metrics.
- Integration with additional machine learning algorithms.

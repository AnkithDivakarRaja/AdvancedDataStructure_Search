## In-memory vs Disk search

Implemented two different search strategies to try to locate each si from the seek list:

__Linear search__: A sequential search of K for a key that matches the current seek value si.

__Binary search__: A binary search through a sorted list of keys K for a key that matches the current seek value si. The fact that the keys are sorted allows approximately half the remaining keys to be ignored from consideration during each step of the search.

Each of the two searches (linear and binary) was performed in two different environments. In the first, the key list K will be held completely in memory. In the second, individual elements ki ∈ K was read from disk as they are needed.

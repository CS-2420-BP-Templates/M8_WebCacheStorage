# Web Cache Simulator

Web browsers use caches to temporarily store information about websites. When a browser requests a URL, it can check the cache to see whether that URL is already stored. If the URL is in the cache, the request is a cache hit. If the URL is not in the cache, the request is a cache miss.

In this assignment, you will implement a hashtable that stores URLs and use it to create a web cache simulator.

You will complete two main tasks:

1. Implement a hashtable using open addressing and linear probing.
2. Write a cache simulator in main() that reads commands from a file, processes cache operations, and calculates the cache hit rate.

## Part 1: Implement the HashTable Class
Complete the provided HashTable class. Your implementation will store URLs as strings and use open addressing with linear probing to resolve collisions.

The provided header file defines the class interface. Implement the required functions in HashTable.cpp.

---

### Hash Function
Implement the hashFunction() to convert a URL into a valid index in the hashtable 

For this assignment, you may calculate the sum of the character codes in the URL and use the modulo operator to determine the index.

Your function must return an index between 0 and capacity() - 1.

---

### Insert: 


Implement insert() to add a URL to the hashtable.

Your implementation must:
- Start at the index returned by the hash function.
- Use linear probing to find an available bucket.
- Wrap around to index 0 when reaching the end of the table.
- Avoid storing duplicate URLs.
- Reuse deleted buckets when appropriate.
- Return true when the operation succeeds and false when insertion is unsuccessful.
- Update the number of stored URLs correctly.
---
### Search
Implement search() to determine whether a URL exists in the hashtable.

- Start at the URL's hash index.
- Use linear probing to handle collisions.
- Continue searching past deleted buckets.
- Stop searching when it reaches a bucket that has never been used.
- Examine no more than the total number of buckets.
- Return true if the URL is present and false otherwise.

---

### Remove
Implement remove() to remove a URL from the hashtable.

Your implementation must:
- Use linear probing to locate the URL.
- Mark the bucket as deleted rather than treating it as a bucket that has never been used.
- Return true if the URL is successfully removed and false if it is not found.
- Update the number of stored URLs correctly.
- Preserve the ability to search for other URLs that occur later in the probe sequence.



## Important: Handling Deleted Buckets

Each bucket has two Boolean variables: empty and deleted. Together, these variables represent three possible states.

| State| Empty | Deleted | Meaning |
| -------- | -------- | -------- | -------- |
| Starting State | true | false | The bucket has never been used |
| Item Inserted | false | false | The bucket currently contains a URL |
| Item Removed | true | true | The URL was removed, but the bucket may be reused |
| Invalid State | false | true | This combination should never occur |

These states help you determine when to continue probing and when to stop.
***Insert***
- Start at the index returned by the hash function.
- If the URL already exists, do not insert a duplicate.
- If you encounter a deleted bucket, remember its position and continue searching in case the URL already exists farther along the probe sequence.
- If you reach a bucket that has never been used, insert the URL into the first deleted bucket you encountered, if there is one. Otherwise, insert into the never-used bucket.
- If you examine every bucket without finding the URL or an available position, return false.

***Search***
- Start at the index returned by the hash function.
- If you find the URL in a bucket that has not been deleted, return true.
- If you encounter a deleted bucket, continue searching.
- If you reach a bucket that has never been used, return false because the URL cannot occur farther along this probe sequence.
- If you examine every bucket without finding the URL, return false.

***Remove***

- Start at the index returned by the hash function.
- If you find the URL in a bucket that has not been deleted, mark the bucket as deleted by setting empty and deleted to true. Update the number of stored URLs and return true.
- If you encounter a deleted bucket, continue searching.
- If you reach a bucket that has never been used, return false because the URL is not in the table.
- If you examine every bucket without finding the URL, return false.

Remember: A deleted bucket is available for reuse, but it cannot be treated like a bucket that has never been used. Searches and removals must continue past deleted buckets to avoid missing URLs that were placed farther along the probe sequence.

## Part 2: Create the Cache Simulator

After completing the HashTable class, write the cache simulator in main().

Your program will read a sequence of cache operations from an input file and use your hashtable to process them.

The input file contains three types of commands:

| Command | Description |
| -------- | -------- |
| INSERT | Add a URL to the cache |
| SEARCH | Check whether a URL is currently cached |
| REMOVE | Remove a URL from the cache |

For example
```angular2html
INSERT https://www.google.com
INSERT https://www.youtube.com
SEARCH https://www.google.com
SEARCH https://www.github.com
REMOVE https://www.youtube.com
SEARCH https://www.youtube.com
```

## Cache Simulator Requirements
Your main() should
1. Open and read the input file.
2. Create a HashTable with the specified capacity.
3. Process each command and its associated URL.
4. Call the appropriate hashtable function for each command.
5. Track cache hits and cache misses.
6. Display the results of the cache operations.
7. Calculate and display the final cache hit rate.


## Tracking Cache Hits and Misses
A cache hit occurs when a SEARCH command finds the requested URL in the cache.

A cache miss occurs when a SEARCH command does not find the requested URL.

Only SEARCH commands count toward the hit rate. INSERT and REMOVE commands do not count as cache requests.

Maintain counters for cache hits and cache misses.

For each SEARCH command
- If the URL is found, increment the cache hit counter.
- If the URL is not found, increment the cache miss counter.

```angular2html
Hit Rate = Hits / (Hits + Misses) * 100
```

## Display the Results
Your program should display the results of processing the commands, including whether searches result in hits or misses and whether insertions and removals succeed.

At the end of the simulation, display:
- Total cache hits.
- Total cache misses.
- Final number of URLs stored in the cache.
- Cache hit rate as a percentage.
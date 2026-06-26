// author: Subham Santra
// purpose: I am bored, I want to code something without using AI
// date: 2026-06-27

#include <iostream>
#include <algorithm>
#include <climits>


using namespace std;

int query_segment_tree(
    int* segment_tree,
    int tree_index,
    int low,
    int high,
    int query_low,
    int query_high
) {
    // base case:
    // if the current segment is completely outside the query range
    if (query_low > high || query_high < low) {
        return INT_MAX; // return a value that won't affect the min operation
    }

    // if the current segment is completely inside the query range
    if (query_low <= low && query_high >= high) {
        return segment_tree[tree_index];
    }

    // if the current segment is partially inside and partially outside the query range
    int mid = low + ((high - low) >> 1);
    return min(
        query_segment_tree(
            segment_tree,
            2 * tree_index + 1,
            low,
            mid,
            query_low,
            query_high),

        query_segment_tree(
            segment_tree,
            2 * tree_index + 2,
            mid + 1,
            high,
            query_low,
            query_high
        )
    );
}

void build_segment_tree(
    int* input_array,
    int* segment_tree,
    int tree_index,
    int low,
    int high
) {
    // base case:
    // when low == high, we have reached a leaf node in the segment tree
    if (low == high) {
        segment_tree[tree_index] = input_array[low];
        return;
    }


    // safe way to calculate mid to avoid integer overflow
    int mid = low + ((high - low) >> 1);

    // recursively build the left subtree
    build_segment_tree(
        input_array,
        segment_tree,
        2 * tree_index + 1,
        low,
        mid
    );

    // recursively build the right subtree
    build_segment_tree(
        input_array,
        segment_tree,
        2 * tree_index + 2,
        mid + 1,
        high
    );

    // after building the left and right subtrees,
    // we can calculate the value of the current node
    segment_tree[tree_index] = min(
        segment_tree[2 * tree_index + 1],
        segment_tree[2 * tree_index + 2]
    );
}

int main() {
    // Take Input
    int n;
    int* input_array;
    int* segment_tree;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    // allocate memory for the input array
    input_array = new int[n];
    segment_tree = new int[4 * n];

    // fill default values in the segment tree
    for (int i = 0; i < 4 * n; i++) {
        segment_tree[i] = INT_MAX;
    }

    // take input for the array
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> input_array[i];
    }

    // build the segment tree
    build_segment_tree(
        input_array,
        segment_tree,
        0,      // root index of the segment tree
        0,      // low index of the input array
        n - 1   // high index of the input array
    );

    //* ASK QUERIES */
    int nq;
    cout << "Enter the number of queries: ";
    cin >> nq;

    for (int i = 0; i < nq; i++) {
        int query_low, query_high;
        cout << "Enter the range for query " << (i + 1) << " (low high): ";
        cin >> query_low >> query_high;

        // validate the query range
        if (query_low < 0 || query_high >= n || query_low > query_high) {
            cout << "Invalid range. Please enter a valid range." << endl;
            i--; // decrement i to repeat this iteration
            continue;
        }

        int result = query_segment_tree(
            segment_tree,
            0,          // root index of the segment tree
            0,          // low index of the input array
            n - 1,      // high index of the input array
            query_low,  // low index of the query range
            query_high  // high index of the query range
        );

        cout << "Minimum value in the range [" << query_low << ", " << query_high << "] is: " << result << endl;
    }

    // deallocate memory
    delete[] input_array;
    delete[] segment_tree;

    return 0;
}
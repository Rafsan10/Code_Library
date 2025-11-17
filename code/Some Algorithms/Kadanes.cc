// return maximum subarray sum.
int kadanes(int arr[], int n) {
    int maxsum = arr[0], curr_sum = arr[0];
    for (int i = 1; i < n; i++) {
        curr_sum = max(arr[i], curr_sum + arr[i]);
        maxsum = max(maxsum, curr_sum);
    }
    return maxsum;
}
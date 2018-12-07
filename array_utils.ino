//void fill(CRGB arr[], int arr_size, CRGB color) {
//  for (int i = 0; i < arr_size; i++) {
//    arr[i] = color;
//  }
//}

void fill(int arr[], int arr_size) {
  for (int i = 0; i < arr_size; i++) {
    arr[i] = i;
  }
}

void shuffle(int arr[], int arr_size) {
  for (int i = 0; i < arr_size / 2; i++) {
    int i1 = random(arr_size);
    int i2 = random(arr_size);
    swap(indexes, i1, i2);
  }
}

void swap(int arr[], int l, int r) {
  int tmp = arr[r];
  arr[r] = arr[l];
  arr[l] = tmp;
}

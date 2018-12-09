#ifndef ARRAYS
#define ARRAYS 1

class Arrays {
  public:
    static void shuffle(XY arr[], int arr_size) {
      for (int i = 0; i < arr_size / 2; i++) {
        int i1 = random(arr_size);
        int i2 = random(arr_size);
        swap(arr, i1, i2);
      }
    }

    static void swap(XY arr[], int l, int r) {
      XY tmp = arr[r];
      arr[r] = arr[l];
      arr[l] = tmp;
    }
};

#endif

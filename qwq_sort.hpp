#ifndef QWQ_SORT_HPP
#define QWQ_SORT_HPP

namespace qwq_sort {
    template<typename T>
    inline void swap(T& op1, T& op2) {
        T tmp = op1;
        op1 = op2;
        op2 = tmp;
    }

    template <typename T>
    inline void bubble_sort(T& arr, size_t size) {
        size_t cnt = 0;
        for (size_t ptr_1 = 0; ptr_1 < size - 1; ptr_1++) 
            for (size_t ptr_2 = 0; ptr_2 < size - 1 - ptr_1; ptr_2++) 
                if (arr[ptr_2] > arr[ptr_2 + 1]) 
                    swap(arr[ptr_2], arr[ptr_2 + 1]);
    }

    template <typename T>
    inline void selection_sort(T& arr, size_t size) {
        for (size_t ptr_1 = 0; ptr_1 < size - 1; ptr_1++) {
            size_t min_idx = ptr_1;
            for (size_t ptr_2 = ptr_1 + 1; ptr_2 < size; ptr_2++) 
                if (arr[ptr_2] < arr[min_idx])
                    min_idx = ptr_2;
            swap(arr[ptr_1], arr[min_idx]);
        }
    }

    template <typename T>
    inline void insertion_sort(T& arr, size_t size) {
        for (size_t ptr_1 = 1; ptr_1 < size; ptr_1++) {
            size_t key   = arr[ptr_1];
            T ptr_2 = ptr_1 - 1;
            while (ptr_2 >= 0 && arr[ptr_2] > key) {
                arr[ptr_2 + 1] = arr[ptr_2];
                ptr_2--;
            }
            arr[ptr_2 + 1] = key;
        }
    }

    template <typename T, size_t N>
    inline void quick_sort(T (&arr)[N], size_t l, size_t r) {
        if (l >= r) return;
        int i = static_cast<int>(l - 1);
        int j = static_cast<int>(r + 1);
        T x = arr[(l + r) >> 1];
        
        while (i < j) {
            do i++; while (arr[i] < x);
            do j--; while (arr[j] > x);
            if (i < j) swap(arr[i], arr[j]);
        }
        quick_sort(arr, l, j), quick_sort(arr,j + 1, r);
    }

    template <typename T>
    inline void merge_sort(T arr[], size_t l, size_t r) {
        static T* tmp = nullptr;
        if(tmp == nullptr) tmp = new T[r - l + 1];
        if (l >= r) return;
        size_t mid = (l + r) >> 1;
        merge_sort(arr, l, mid), merge_sort(arr, mid + 1, r);
            
        size_t k = 0, i = l, j = mid + 1;
        while (i <= mid && j <= r) {
            if (arr[i] < arr[j]) tmp[k++] = arr[i++];
            else                 tmp[k++] = arr[j++];  
        }
        while (i <= mid) tmp[k++] = arr[i++];
        while (j <= r) tmp[k++] = arr[j++];

        for (i = l, j = 0; i <= r; i++, j++) arr[i] = tmp[j];
    }
}
#endif
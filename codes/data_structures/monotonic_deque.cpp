struct MonotonicDeque {
    deque<pair<int, int>> dq; // {val, idx}
    int k; // window size
    MonotonicDeque(int _k) : k(_k) {}
    
    void push(int value, int index) { // insert at i
        while (!dq.empty() && dq.back().first >= value) dq.pop_back();
        dq.emplace_back(value, index);
    }

    void pop(int index) {// remove elements outside the window
        while (!dq.empty() && dq.front().second <= index - k) dq.pop_front();
    }

    int get_min() {
        if (dq.empty()) return -1; 
        return dq.front().first;
    }
};
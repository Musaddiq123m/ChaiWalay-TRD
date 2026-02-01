vector<int> makeCoordinateArray(const vector<int>& values) {
    vector<int> comp = values;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    return comp;
}

class FenwickCount {
    vector<int> bit;        
    vector<int> comp;       
    vector<int> arr;        
    int n;
    
    void updateBIT(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }
    
    int prefixSum(int idx) const {
        int s = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    }

    int getId(int x) const {
        return (int)(lower_bound(comp.begin(), comp.end(), x) - comp.begin());
    }

public:
    FenwickCount(const vector<int>& arrInit, const vector<int>& coordArray) {
        arr = arrInit;
        comp = coordArray;
        n = comp.size();
        bit.assign(n+1, 0);
        
        for (int x : arr) {
            updateBIT(getId(x), 1);
        }
    }
    
    int query(int x) const {
        int id = (int)(upper_bound(comp.begin(), comp.end(), x) - comp.begin()) - 1;
        if (id < 0) return 0;
        return prefixSum(id);
    }
    
    void updateValue(int idx, int newVal) {
        int oldVal = arr[idx];
        updateBIT(getId(oldVal), -1);
        updateBIT(getId(newVal), +1);
        arr[idx] = newVal;
    }
};

/*
Usage of query for other comparisons:
---------------------------------------
- count(< x)   = query(x - 1) 
- count(<= x)  = query(x)
- count(> x)   = totalSize - query(x)
- count(>= x)  = totalSize - query(x - 1)
- count(== x)  = query(x) - query(x - 1)
*/
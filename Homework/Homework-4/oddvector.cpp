void removeOdd(vector<int>& v)
{
    vector<int>::iterator p;
        p = v.begin();
        while (p != v.end()) {
            if ((*p) % 2 == 1) {
                p = v.erase(p);
            }
            else
                p++;
        }

}

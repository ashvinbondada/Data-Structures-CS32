void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator p;
        p = v.begin();
        while (p != v.end()) {
            if ((*p)->rating() < 50) {
                delete (*p);
                p = v.erase(p);
            }
            else
                p++;
        }
}

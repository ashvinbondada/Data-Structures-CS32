void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator p;
    p = li.begin();
    while (p != li.end()) {
        if ((*p)->rating() < 50) {
            delete (*p);
            p = li.erase(p);
        }
             
        else
            p++;
    }
}

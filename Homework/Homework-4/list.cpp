void listAll(string path, const Class* c)  // two-parameter overload
{
   //You will write this code.
    if (c != nullptr) {
        string end = path + c->name();
        cout << end << endl;
    }
    vector<Class*>::const_iterator p;
    p = c->subclasses().begin();
    while (p != c->subclasses().end()) {
        string append = path + c->name() + "=>";
        listAll(append, (*p++));
    }
}

#include <iostream>

using namespace std;

//Linked List
struct N {
    int d;  //Data
    N* n;   //Pointer
    N(int val) : d(val), n(nullptr) {}  
};

//Hashed Linked List
class L {
private:
    N* h;      //1st node of the list
    int len;   //Size(list)
    long long t;  //Hash value
    const int b = 37;  //Base
    const long long MOD = 1e9 + 9;  //Using a large prime number

public:
    L() : h(nullptr), len(0), t(0) {} //Initialize the Linked list

    void a(int v) {
        N* newN = new N(v);

        if (h == nullptr) { //List empty case
            h = newN;
        } else {

            N* curr = h;
            while (curr->n != nullptr) {
                curr = curr->n;
            }
            curr->n = newN;  //Node at end
        }

        //List size update and hash value
        len++;
        t = (t * b + v) % MOD;
    }

    //Search list
    bool f(int v) {
        N* curr = h;
        while (curr != nullptr) {
            if (curr->d == v) {
                return true;
            }
            curr = curr->n;
        }
        return false;
    }

    //Remove from List
    void r(int v) {
        N* curr = h;
        N* prev = nullptr;
        int idx = 0;

        //Find the value to be removed
        while (curr != nullptr) {
            if (curr->d == v) {
             
                long long pow = p(b, len - idx - 1, MOD);
                t = (t - v * pow) % MOD;
                if (t < 0) {
                    t += MOD;  
                }

                len--;  //Reduce list size

                //remove node
                if (prev == nullptr) {
                    h = curr->n;  
                } else {
                    prev->n = curr->n;
                }
                delete curr; 
                return;
            }
            prev = curr;
            curr = curr->n;
            idx++;  //Node position 
        }
    }

    //Compare two linked lists based on their hash values
    bool e(L& o) {
        if (len != o.len) {
            return false;  //Need the lists to be same size for them to be equivalent
        }
        return t == o.t;  //Hash values comparison
    }

//Helper fucntion
    long long p(long long b, int exp, long long m) {
        long long res = 1;
      
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = (res * b) % m;
            }
            b = (b * b) % m;
            exp /= 2;
        }
        return res;
    }

    
    void pr() {
        N* curr = h;
        while (curr != nullptr) {
            cout << curr->d << " -> ";
            curr = curr->n;
        }
        cout << "NULL" << endl;
    }
};

//Test
int main() {
    L l1; 
    L l2;  

    //List 1 Insert
    l1.a(56);
    l1.a(48);
    l1.a(13);


    l2.a(56);
    l2.a(48);
    l2.a(13);

    if (l1.e(l2)) {
        cout << "Equivalent lists" << endl;
    } else {
        cout << "Not equivalent" << endl;
    }



    return 0;
}

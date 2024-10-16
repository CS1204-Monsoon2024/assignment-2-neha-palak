#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
    public:
        double load_fact = 0.8;
        int m;
        int size = 0;
        std::vector<int> table;

        HashTable(int initialSize) {
            m = initialSize;
            table.resize(m, -1); 
        }

        void insert(int value){
            checkIfResize();
            int key = quadratic_probe(value);
            if(key == -1){
                cout << "Max probing limit reached!" << endl;
                return;
            } else if(key == -2){
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }

            table[key] = value;
            size ++;
        }

        void remove(int value){
            int key = quadratic_probe_search(value);
            if(key == -1){
                cout << "Element not found" << endl;
                return;
            }
            table[key] = -1;
            size --;
        }

        int search(int value){
            return quadratic_probe_search(value);
        }

        void printTable(){
            for(auto itr : table){
                if(itr == -1){
                    cout << "-" << " ";
                }else{
                    cout << itr << " ";
                }
            }
            cout << '\n';
            return;
        }

    private:
        void checkIfResize(){
            if((double)size / (double)m > load_fact) {
                m = getNewSize();
                std::vector<int> new_table(m, -1);
                table.swap(new_table);
                size = 0;
                for(auto itr: new_table){
                    if(itr == -1){
                        continue;
                    }
                    else{
                        insert(itr);
                    }
                }
                // Deallocate memory
                new_table = std::vector<int>();
            }
        }

        int getNewSize(){
            int new_size = m * 2 + 1;
            while(!isPrime(new_size)){
                new_size ++;
            }
            return new_size;
        }

        bool isPrime(int n){
            int i;
            double sqrt_n = sqrt(n) ;
            for (i = 2; i <= sqrt_n ; i++)
            {
                if (n % i == 0){
                    return false;
                    break;
                }
            }
            return true;

        }

        int hash(int value){
            return value % m;
        }
        
        int quadratic_probe(int value){
            int max = (m + 1) / 2;
            int key;
            bool found = false;

            for(int step=0; step <= max; step++){
                key = (hash(value) + step*step) % m;
                if(table[key] == -1){
                    found = true;
                    break;
                } else if(table[key] == value){
                    return -2;
                }

            }
            
            if(found == false){
                return -1;
            }
            else{
                return key;
            }
        }

        int quadratic_probe_search(int value){
            int max = (m + 1) / 2;
            int key;

            for(int step = 0; step <= max; step++){
                key = (hash(value) + step*step) % m;
                if(table[key] == -1){
                    return -1;

                }else if (table[key] == value){
                    return key;
                }
                

            }

            return -1;
        }
};
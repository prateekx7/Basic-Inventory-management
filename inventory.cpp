#include <bits/stdc++.h>
using namespace std;

class Product
{
    private:
        int id;
        string name;
        string category;
        double price;
        int quantity;
        //ID,Name,Category,Price,Quantity
    
    public:
        Product(int id, string name, string category, double price, int quantity)
        {
            this->id=id;
            this->name=name;
            this->category=category;
            this->price=price;
            this->quantity=quantity;
        }

        int getId() const{
            return id;
        }

        void setId(int id){
            this->id=id;
        }

        string getName() const{
            return name;
        }

        void setName(string name){
            this->name=name;
        }

        string getCategory() const{
            return category;
        }

        void setCategory(string category){
            this->category=category;
        }

        double getPrice() const{
            return price;
        }

        void setPrice(double price){
            this->price=price;
        }

        int getQuantity() const{
            return quantity;
        }

        void setQuantity(int quantity){
            this->quantity=quantity;
        }
};

class Inventory
{
    private:
        vector<Product> products;
    
    public:
        void addProduct(Product product)
        {
            bool found = false;
            for (auto& p : products)
            {
                if (p.getId() == product.getId())
                {
                    cout << "Id already Exist."<< endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                products.push_back(product);
                cout << "Product added successfully." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
        }            

        void removeProduct(int id, const string& filename)
        {
            bool found = false;
            vector<Product> updatedProducts;
 
            for (const auto& product : products)
            {
                if (product.getId() != id)
                {
                    updatedProducts.push_back(product); 
                }
                else
                {
                    found = true; 
                }
            }

            if (found)
            {
                products = updatedProducts; 

                
                ofstream file(filename, ios::out);
                if (file.is_open())
                {
                    for (const auto& product : products)
                    {
                        file << product.getId() << ","
                            << product.getName() << ","
                            << product.getCategory() << ","
                            << product.getPrice() << ","
                            << product.getQuantity() << endl;
                    }
                    file.close();
                    cout << "Product removed successfully and file updated." << endl;
                    cout << "-----------------------------------------------------------" << endl;
                }
                else
                {
                    cout << "Error: Could not open file " << filename << endl;
                }
            }
            else
            {
                cout << "ID does not exist." << endl; 
            }
        }


        Product* findProduct(int id)
        {
            for(auto i=products.begin();i!=products.end();i++)
            {
                if(i->getId()==id)
                {
                    return &(*i);
                }
            }
            return nullptr;
        }

        void updateProduct(int id, string name, string category, double price, int quantity)
        {
            bool found = false;
            for (auto i = products.begin(); i != products.end(); i++)
            {
                if (i->getId() == id)
                {
                    i->setName(name);
                    i->setCategory(category);
                    i->setPrice(price);
                    i->setQuantity(quantity);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "ID does not exist." << endl;
            }
        }        

        void printProduct() const{
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<endl;
                cout<<"Name : "<<i->getName()<<endl;
                cout<<"Category : "<<i->getCategory()<<endl;
                cout<<"Price : ₹"<<i->getPrice()<<endl;
                cout<<"Quantity : "<<i->getQuantity()<<endl;
            }
        }

        void saveInventoryToFile(string filename) 
        {
            ofstream file;
            file.open(filename, ios::out); 

            if (file.is_open()) 
            {
                for (const auto& product : products) 
                {
                    file << product.getId() << "," 
                        << product.getName() << "," 
                        << product.getCategory() << "," 
                        << product.getPrice() << "," 
                        << product.getQuantity() << endl;
                }
                file.close();
                cout << "Inventory saved to file." << endl;
            } 
            else 
            {
                cout << "Error: Could not open file " << filename << endl;
            }
        }
            

    void loadInventoryFromFile(string filename) 
    {
        ifstream file;
        file.open(filename);

        if (file.is_open()) 
        {
            string line;
            while (getline(file, line)) 
            {
                if (line.empty()) 
                    continue;
                stringstream ss(line);
                string idStr, name, category, priceStr, quantityStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, category, ',');
                getline(ss, priceStr, ',');
                getline(ss, quantityStr, ',');

                if (idStr.empty() || name.empty() || category.empty() || priceStr.empty() || quantityStr.empty()) {
                    cout << "Warning: Skipping invalid line: " << line << endl;
                    continue;
                }

                try{
                    int id = stoi(idStr);
                    double price = stod(priceStr);
                    int quantity = stoi(quantityStr);

                    Product p(id, name, category, price, quantity);
                    products.push_back(p);
                } catch (const invalid_argument& e) {
                    cout << "Skipped invalid line: " << line << endl;
                }
            }

            file.close();
        } else {
            cout << "Error: Could not open file " << filename << endl;
        }
    }
};

int main() {
    Inventory inventory;
    cout << "-----------------------------------------------------------" <<endl;
    cout << "---------------Inventory Management System ----------------" <<endl;   
    cout << "-----------------------------------------------------------" <<endl;
    cout << "------------------------- Welcome! ------------------------" <<endl;
    cout << "-----------------------------------------------------------" <<endl;
    char choice;
    do {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Save inventory to file" << endl;
        cout << "7. Load Inventory from file" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: ₹ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }

        case '2': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id, "inventoryFile.csv");
            break;
        }

        case '3': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            Product* product = inventory.findProduct(id);
            if (product) {
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: ₹ " << product->getPrice() << endl;
                cout << "Quantity: " << product->getQuantity() << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
            else {
                cout << "Product not found." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
            break;
        }

        case '4': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: ₹ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }

        case '5': {
            inventory.printProduct();
            break;
        }
        case '6': {
            inventory.saveInventoryToFile("inventoryFile.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case '7': {
            inventory.loadInventoryFromFile("inventoryFile.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
        case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            return 0;
        
        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        }
    } while (true);

    return 0;
}
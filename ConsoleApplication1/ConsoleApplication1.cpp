#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Product {
    std::string name;
    double price;
    int quantity;

    Product(const std::string& n, double p, int q) : name(n), price(p), quantity(q) {}
};

struct Transaction {
    
    std::vector<Product> itemsPurchased;
    
    double totalBill;

    Transaction() : totalBill(0.0) {};
};

std::vector<Product> inventory;
std::vector<Transaction> transactions;

bool authenticateUser() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;
    if (username == "root" && password == "1234") {
        return true;
    }
    else {
        std::cout << "Invalid username or password. Authentication failed.\n";
        return false;
    }
}

void displayProducts(const std::vector<Product>& products) {
    std::cout << "Inventory:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];
        std::cout << i + 1 << ". " << product.name << " - Price: $" << product.price
            << " - Quantity: " << product.quantity << "\n";
    }
}

void addProduct() {
    std::string name;
    double price;
    int quantity;
    std::cout << "Enter product name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter product price: $";
    std::cin >> price;
    std::cout << "Enter product quantity: ";
    std::cin >> quantity;
    inventory.push_back(Product(name, price, quantity));
    std::cout << "Product added to the inventory.\n";
}

void updateProduct() {
    displayProducts(inventory);
    int index;
    std::cout << "Enter the index of the product to update: ";
    std::cin >> index;
    if (index <= 0 || index > inventory.size()) {
        std::cout << "Invalid product index.\n";
        return;
    }
    Product& product = inventory[index - 1];
    double price;
    int quantity;
    std::cout << "Enter updated price: $";
    std::cin >> price;
    std::cout << "Enter updated quantity: ";
    std::cin >> quantity;
    product.price = price;
    product.quantity = quantity;
    std::cout << "Product updated.\n";
}

void removeProduct() {
    displayProducts(inventory);
    int index;
    std::cout << "Enter the index of the product to remove: ";
    std::cin >> index;
    if (index <= 0 || index > inventory.size()) {
        std::cout << "Invalid product index.\n";
        return;
    }
    inventory.erase(inventory.begin() + index - 1);
    std::cout << "Product removed from the inventory.\n";
}



void removeFromCart() {
    if (transactions.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }

    std::vector<Product>& cart = transactions.back().itemsPurchased;
    displayProducts(cart);
    int index;
    std::cout << "Enter the index of the product to remove from the cart: ";
    std::cin >> index;
    if (index <= 0 || index > cart.size()) {
        std::cout << "Invalid product index.\n";
        return;
    }
    Product& product = cart[index - 1];
    cart.erase(cart.begin() + index - 1);

    // Find the corresponding product in the inventory and increment its quantity
    for (Product& invProduct : inventory) {
        if (invProduct.name == product.name) {
            invProduct.quantity++;
            break;
        }
    }

    std::cout << "Product removed from the cart.\n";




}


void saveInventoryToFile(const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const Product& product : inventory) {
            file << product.name << "," << product.price << "," << product.quantity << "\n";
        }

        file.close();
        std::cout << "Inventory data saved to " << filename << ".\n";
    }
    else {
        std::cout << "Error: Unable to open file for saving.\n";
    }
}
void billing() {
    std::string name;
    int age;
    int total = 0;
    std::cout << "Enter Buyer Name ------------------------>>>>>";
    std::cin >> name;
    std::cout << "Enter Age--------------------------------->>>>";
    std::cin >> age;
    displayProducts(inventory);
    bool exitRequested = false;
    
    int i = 0;
    int arr[1000];
    std::string Array[1000];
    for (int i = 0; i < 3; i++) {
        std::cout << "| |\n";
    }
    while (!exitRequested) {
        int index;
        int quantity;

        std::cout << "Enter the index of the product to add to the cart: ---------------------------------->>>>>>>";

        std::cin >> index;

        std::cout << "Enter the quantity of the product to add: ----------------------------------->>>>>>>>>";
        std::cin >> quantity;
        arr[i] = quantity;
        
        i = i + 1;
        for (int i = 0; i < 3; i++) {
            std::cout << "| |\n";
        }


        if (index <= 0 || index > inventory.size()) {
            std::cout << "Invalid product index.\n";
            return;
        }
        Product& product = inventory[index - 1];
        if (product.quantity > 0) {
            
            product.quantity = product.quantity - quantity;
            



            if (transactions.empty()) {
                transactions.push_back(Transaction());
            }


            transactions.back().itemsPurchased.push_back(product);
           

        }
        else {
            std::cout << "Product is out of stock.\n";
        }

        std::string choice;
        std::cout << "^^^^^^^^^^^^^^^^^^^^^Do you want to continue?????????????????????? (y/n):         ";
        std::cin >> choice;


        if (choice == "y" || choice == "Y") {
            exitRequested = false;

        }
        else {
            exitRequested = true;
        }


    }
    for (int i = 0; i < 3; i++) {
        std::cout << "| |\n";
    }
    std::string rem;
    std::cout << "    Want to remove any product from cart?????????????????-------------<<<";
    std::cin >> rem;
    if (rem == "y" || rem == "Y") {
        if (transactions.empty()) {
            std::cout << "Cart is empty.\n";
            return;
        }

        std::vector<Product>& cart = transactions.back().itemsPurchased;
        displayProducts(cart);
        int index;
        std::cout << "Enter the index of the product to remove from the cart:-------------------<<<<<<< ";
        std::cin >> index;
        if (index <= 0 || index > cart.size()) {
            std::cout << "Invalid product index.\n";
            return;
        }
        Product& product = cart[index - 1];
        cart.erase(cart.begin() + index - 1);

       
        for (Product& invProduct : inventory) {
            if (invProduct.name == product.name) {

                invProduct.quantity++;
                break;
            }
        }

        std::cout << "Product removed from the cart.\n";
        std::cout << "   \n";
    }
    else{
        std::string c;
        std::cout << "$$$$$$$$$$$$$$$$$$$Do you want to confirm purchase???????------------>>>>>>>>";
        std::cin >> c;
        const std::vector<Product>& cart = transactions.back().itemsPurchased;
        double totalBill = 0.0;
        int w = 0;
        for (const Product& product : cart) {
            totalBill += product.price * (arr[w]);
            w++;
        }

        if (c == "Y" || c == "y") {
            const Transaction& currentTransaction = transactions.back();
            std::cout << "Cart Contents:\n";
            int r = 0;
            for (size_t i = 0; i < currentTransaction.itemsPurchased.size(); ++i) {

                const Product& product = currentTransaction.itemsPurchased[i];
                std::cout << i + 1 << ". " << product.name << " ||  Price: $" << product.price << " || Quantity: " << arr[r] << "\n"<<"\n";
                r++;
                std::cout << "-----------------\n";
                

            }
            std::cout << "\n";
            std::cout << "---------------------------------------Total Bill: $-------------------------------------" << "\n";
            std::cout << "--------------------------------------" << totalBill << "------------------------------------- << " << "\n";
                std::cout << "\n";
            std::cout << "                                          Mode of payment                ---->>";
            std::string mop;
            std::cin >> mop;
            std::cout << "------------------Saving Bill-----------------------------";
            for (int i = 0; i <= 4; i++) {
                std::cout << "................\n";
            }
            const std::string inventoryFil = "Bill.txt";
            std::ofstream file(inventoryFil);

            if (file.is_open()) {
                file << "Customer Name" << name << ", Customer Age" << age << ", Mode of Payement" << mop << "\n";

                int u=0;
                for (const Product& product : inventory) {
                    if (u == 2) {
                        break;
                    }

                    file << "Product -- " << product.name << ", Price -- " << product.price << ", Quantity -- " << arr[u] << "\n";
                    ++u;
                    


                }file << "......................................................." << "\n";
              
                file << "\n";

                file.close();
                std::cout << "----------------------------------------------------Bill saved to " << inventoryFil << "--------------------------------.\n";
            }
            else {
                std::cout << "Error: Unable to open file for saving.\n";
            }


        }



    }
}
void readfile(const std::string& filename) {


    std::ifstream read(filename);

    std::string line;
    while (std::getline(read, line)) {
        std::cout << line << '\n';
    }

    read.close();
}
void loadInventoryFromFile(const std::string& filename) {
    std::ifstream read(filename);

    if (read.is_open()) {
        std::string line;
        while (std::getline(read, line)) {
            std::stringstream ss(line);
            std::string name;
            double price;
            int quantity;
            if (std::getline(ss, name, ',') && ss >> price && ss.ignore() && ss >> quantity) {
                inventory.push_back(Product(name, price, quantity));
            }
        }
        read.close();
        std::cout << "Inventory data loaded from " << filename << ".\n";
    }
    else {
        std::cout << "Error: Unable to open file for loading.\n";
    }
}

int main() {
    const std::string inventoryFile = "inventoryt.txt";
    const std::string billfile = "bill.txt";

    loadInventoryFromFile(inventoryFile);

    if (!authenticateUser()) {
        std::cout << "Authentication failed. Exiting.\n";
        return 1;
    }

    while (true) {
        std::cout << "_____________------------Supermarket Management System---------------------_________________\n";
        std::cout << "                       1. Display Products in Inventory\n";
        std::cout << "                       2. Inventory Management\n";
        std::cout << "                       3. Billing System\n";
        std::cout << "                       4. Save Inventory Data\n";
        std::cout << "                       5. Exit\n";

        std::cout << "Enter your choice: -------------------->>>>>";
        int choices = 0;
        std::cin >> choices;
        switch (choices) {
        case 1:
            displayProducts(inventory);
            break;
        case 2:
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Inventory Management:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            std::cout << "                              1. Add Product to Inventory\n";
            std::cout << "                              2. Update Product in Inventory\n";
            std::cout << "                              3. Remove Product from Inventory\n";
            std::cout << "                              4. Back to Main Menu\n";
            int inventoryChoice;
            std::cout << "Enter your choice: -------------------------->>>>.";
            std::cin >> inventoryChoice;
            switch (inventoryChoice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                removeProduct();
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
            break;
        case 3:
            std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Billing System:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
            std::cout << "                              1. New Bill                                       \n";
            std::cout << "                              2. Previous Bill                                          \n";
            int billingChoice;
            std::cout << "Enter your choice:--------------------------------------->>>>>>>>> ";
            std::cin >> billingChoice;
            switch (billingChoice) {
            case 1:
                billing();
                break;
            case 2:
                readfile(billfile);
                break;
            case 4:
                saveInventoryToFile(inventoryFile);
                break;
            case 5:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
            }
            break;
        case 4:
            saveInventoryToFile(inventoryFile);
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

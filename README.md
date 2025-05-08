
# 🍕 Pizza Ordering System (C++ Console Application)

## 📌 Description

This is a console-based C++ application for ordering pizza. It allows users to register or log in with a phone number, browse a pizza menu, add or remove items from the cart, view the order summary, and save the final order and customer details to a file.

## 🛠 Features

- 📱 Phone number validation (UZB format: `+998`)
- 🔄 Load existing customer data from `order.txt` if available
- 🍕 Display and select from a predefined pizza menu
- 🛒 Add and remove pizzas from the shopping cart
- 💸 Automatic total and cashback calculation (3%)
- ✏️ Update customer information
- 💾 Save order and customer details to a file

## 📂 File Structure

- `struct Pizza` — defines pizza name and price  
- `struct Customer` — stores customer personal information  
- `class PizzaOrder` — handles customer registration, cart management, menu display, file saving/loading, and main program loop

## 🚀 How to Run

1. **Compile the file:**

   ```bash
   g++ "final exam (2).cpp" -o PizzaOrder
````

2. **Run the executable:**

   ```bash
   ./PizzaOrder
   ```

3. **Follow the console prompts:**

   * Enter a valid phone number
   * Register or log in
   * Choose pizzas and manage your order through the main menu

## 📁 Data Storage

All customer and order information is saved in a file named `order.txt` in the same directory.

## 🧾 Menu Items

The pizza menu includes:

* Pepperoni — 100,000 so'm
* Four Cheese — 90,000 so'm
* Meat — 120,000 so'm
* Combo — 130,000 so'm

## ⚙️ Dependencies

Uses only standard C++ libraries:

* `iostream`
* `fstream`
* `string`
* `vector`
* `iomanip`

## 👨‍💻 Author

Developed as part of a final programming exam project.

```

```

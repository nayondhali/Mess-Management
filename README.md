# Mess Management System

A simple C-based console application to manage mess (shared meal) accounts, track members, meals, expenses, and balances.

## Features
- Add, remove, search, and list mess members
- Enter daily meals (lunch & supper) for each member
- Add and view mess expenses
- Calculate meal rate based on total expenses and meals
- Show each member's balance and expense share
- Generate partial and full reports
- Export and reset data

## How It Works
- Each member's expense share is calculated as: `expense_share = meal_rate * total_meals_taken`
- Balance for each member: `balance = deposit - expense_share`
- Data is saved in `mess_data.txt` for persistence

## Usage
1. Compile the code:
   ```sh
   gcc Project_03.c -o Project_03.exe
   ```
2. Run the program:
   ```sh
   Project_03.exe
   ```
3. Follow the menu to manage members, meals, expenses, and view reports.

## File Structure
- `Project_03.c` : Main source code
- `mess_data.txt` : Data file (auto-generated)
- `Project_03.exe` : Compiled executable

## Menu Overview
- **Dashboard**: View overall stats
- **Member Management**: Add, remove, search, deposit
- **Meal Entry**: Enter meals, view meal chart
- **Expense Entry**: Add/view expenses
- **Meal Rate Calculation**: Calculate and display meal rate
- **Balance**: Show each member's balance
- **Reports**: Generate partial/full reports
- **Settings**: Reset or export data

## Notes
- Maximum 100 members, 100 meals, 100 expenses
- All data is stored locally in `mess_data.txt`
- Future enhancements: Monthly reports, advanced filtering

## License
This project is open source and free to use for educational purposes.

#include <bits/stdc++.h>
using namespace std;

class BaseEntity {
protected:
    string name;

public:
    BaseEntity(const string& name) : name(name) {}
    string getName() const { return name; }
    virtual ~BaseEntity() {}
};

class Activity : public BaseEntity {
private:
    float duration;
    float intensityMET;
    float weight;

public:
    Activity(const string& name, float duration, float intensityMET, float weight)
        : BaseEntity(name), duration(duration), intensityMET(intensityMET), weight(weight) {}

    float calculateCaloriesBurned() const {
        return intensityMET * weight * (duration / 60.0);
    }

    void displayActivity() const {
        cout << "Activity: " << name << " | Duration: " << duration
             << " mins | Intensity (MET): " << intensityMET
             << " | Calories Burned: " << calculateCaloriesBurned() << " kcal\n";
    }

    float getDuration() const { return duration; }
};

class Food : public BaseEntity {
private:
    float caloriesPerGram;
    float quantity;
    string foodType;

public:
    Food(const string& name, float caloriesPerGram, float quantity, const string& foodType)
        : BaseEntity(name), caloriesPerGram(caloriesPerGram), quantity(quantity), foodType(foodType) {}

    float calculateTotalCalories() const {
        return caloriesPerGram * quantity;
    }

    void displayFood() const {
        cout << "Food: " << name << " | Quantity: " << quantity
             << " g | Type: " << foodType
             << " | Total Calories: " << calculateTotalCalories() << " kcal\n";
    }

    float getQuantity() const { return quantity; }
};

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value > 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid integer.\n";
    }
    return value;
}

float getValidFloat(const string& prompt) {

    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value > 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number.\n";
    }
    return value;
}

string getValidString(const string& prompt) {
    string value;
    cin.ignore();
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) break;
        cout << "Invalid input. Please enter a non-empty string.\n";
    }
    return value;
}

class ActivityTracker {
private:
    vector<Activity*> activityLog;

public:
    void trackActivity(Activity* activity) {
        activityLog.push_back(activity);
        cout << "Activity logged: " << activity->getName() << endl;
    }

    float calculateTotalCaloriesBurned() const {
        float total = 0;
        for (const auto& activity : activityLog) {
            total += activity->calculateCaloriesBurned();
        }
        return total;
    }

    void displayActivities() const {
        cout << "\n=== Activity Log ===\n";
        for (const auto& activity : activityLog) {
            activity->displayActivity();
        }
        cout << "Total Calories Burned: " << calculateTotalCaloriesBurned() << " kcal\n";
    }

    ~ActivityTracker() {
        for (auto activity : activityLog) {
            delete activity;
        }
    }

    void saveActivities(ofstream& outFile) const {
        for (const auto& activity : activityLog) {
            outFile << activity->getName() << "," << activity->getDuration() << "," << activity->calculateCaloriesBurned() << "\n";
        }
    }
};

class FoodTracker {
private:
    vector<Food*> foodLog;

public:
    void trackFood(Food* food) {
        foodLog.push_back(food);
        cout << "Food logged: " << food->getName() << endl;
    }

    float calculateTotalCaloriesConsumed() const {
        float total = 0;
        for (const auto& food : foodLog) {
            total += food->calculateTotalCalories();
        }
        return total;
    }

    void displayFoods() const {
        cout << "\n=== Food Log ===\n";
        for (const auto& food : foodLog) {
            food->displayFood();
        }
        cout << "Total Calories Consumed: " << calculateTotalCaloriesConsumed() << " kcal\n";
    }

    ~FoodTracker() {
        for (auto food : foodLog) {
            delete food;
        }
    }

    void saveFoods(ofstream& outFile) const {
        for (const auto& food : foodLog) {
            outFile << food->getName() << "," << food->getQuantity() << "," << food->calculateTotalCalories() << "\n";
        }
    }
};

class User : public BaseEntity {
private:
    int age;
    float weight;
    float height;
    string gender;
    string goal;
    ActivityTracker activityTracker;
    FoodTracker foodTracker;

public:
    User(const string& name, int age, float weight, float height, const string& gender, const string& goal)
        : BaseEntity(name), age(age), weight(weight), height(height), gender(gender), goal(goal) {}

    static User inputUserInfo() {
        string name = getValidString("Enter your name: ");

        for (auto& user : usersList) {
            if (user.getName() == name) {
                cout << "Welcome back, " << name << "!\n";
                return user;
            }
        }

        cout << "Creating a new user profile for " << name << "!\n";
        int age = getValidInt("Enter your age: ");
        float weight = getValidFloat("Enter your weight (kg): ");
        float height = getValidFloat("Enter your height (cm): ");
        string gender = getValidString("Enter your gender (Male/Female): ");
        string goal = getValidString("Enter your health goal (e.g., Lose Weight, Gain Weight): ");

        User newUser(name, age, weight, height, gender, goal);
        usersList.push_back(newUser);
        return newUser;
    }

    float getWeight() { return this->weight; }

    void updateUserInfo() {
        cout << "\n=== Update User Info ===\n";
        weight = getValidFloat("Enter new weight (kg): ");
        height = getValidFloat("Enter new height (cm): ");
        goal = getValidString("Enter new health goal: ");
        cout << "User information updated successfully!\n";
    }

    void recordActivity(Activity* activity) {
        activityTracker.trackActivity(activity);
    }

    void recordFood(Food* food) {
        foodTracker.trackFood(food);
    }

    float calculateBMI() const {
        return weight / ((height / 100) * (height / 100));
    }

    string getBMICategory() const {
    float bmi = calculateBMI();
    if (bmi < 18.5) {
        return "Underweight: It's important to focus on gaining healthy weight. Consider increasing calorie intake with nutritious foods, and consult a healthcare provider for personalized advice.";
    }
    else if (bmi < 25) {
        return "Normal: Maintain a balanced diet and stay physically active to keep your weight healthy.";
    }
    else if (bmi < 30) {
        return "Overweight: Consider incorporating regular exercise and making healthier food choices to reach a healthier weight. A healthcare provider can offer personalized guidance.";
    }
    else {
        return "Obese: It's essential to work on achieving a healthier weight through a balanced diet and regular physical activity. Please consult a healthcare professional for tailored advice.";
    }
}

    void getSummary() const {
        cout << "\n=== User Summary ===\n";
        cout << "Name: " << name << " | Age: " << age << " | Gender: " << gender
             << " | BMI: " << fixed << setprecision(2) << calculateBMI()
             << " (" << getBMICategory() << ")\n";
        cout << "Goal: " << goal << endl;
        activityTracker.displayActivities();
        foodTracker.displayFoods();

        float netCalories = foodTracker.calculateTotalCaloriesConsumed() - activityTracker.calculateTotalCaloriesBurned();
        cout << "\nNet Calories: " << fixed << setprecision(2) << netCalories << " kcal\n";

        if (netCalories > 0)
            cout << "You consumed more calories than burned, you may gain weight. \n";
        else if (netCalories < 0)
            cout << "You burned more calories than consumed. You may lose weight. \n";
        else
            cout << "Calories balanced! Keep it up!\n";
    }

    void saveUserData(const string& fileName) {
    vector<User> allUsers = loadUserInfo(fileName);
    bool userExists = false;

    for (auto& user : allUsers) {
        if (user.getName() == name) {
            user = *this; // Update user data
            userExists = true;
            break;
        }
    }

    if (!userExists) {
        allUsers.push_back(*this);
    }

    ofstream outFile(fileName, ios::trunc);
    if (!outFile) {
        cerr << "Error: Unable to open file " << fileName << " for saving user data." << endl;
        return;
    }

    for (const auto& user : allUsers) {
        outFile << "Name: " << user.name << "\n";
        outFile << "Age: " << user.age << "\n";
        outFile << "Weight: " << user.weight << "\n";
        outFile << "Height: " << user.height << "\n";
        outFile << "Gender: " << user.gender << "\n";
        outFile << "Goal: " << user.goal << "\n";

        outFile << "\n=== Activities ===\n";
        user.activityTracker.saveActivities(outFile);

        outFile << "\n=== Foods ===\n";
        user.foodTracker.saveFoods(outFile);

        outFile << "----------------------------------------\n";
    }

    outFile.close();
    cout << "User data saved to " << fileName << "\n";
}

static vector<User> loadUserInfo(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Unable to open file " << fileName << " for loading user data." << endl;
        return {};
    }

    vector<User> usersList;
    string line;

    while (getline(inFile, line)) {
        if (line.find("Name:") == 0) {
            string name = line.substr(6);
            int age;
            float weight, height;
            string gender, goal;

            getline(inFile, line);
            age = stoi(line.substr(5));

            getline(inFile, line);
            weight = stof(line.substr(8, line.find(" kg") - 8));

            getline(inFile, line);
            height = stof(line.substr(8, line.find(" cm") - 8));

            getline(inFile, line);
            gender = line.substr(8);

            getline(inFile, line);
            goal = line.substr(6);

            User user(name, age, weight, height, gender, goal);

            // Skip activities and foods for simplicity here
            string skipLine;
            while (getline(inFile, skipLine) && !skipLine.empty()) {
                if (skipLine == "----------------------------------------") {
                    break;
                }
            }

            usersList.push_back(user);
        }
    }

    inFile.close();
    return usersList;
}

    static vector<User> usersList;
};

vector<User> User::usersList = User::loadUserInfo("user_data.txt");

unordered_map<string, pair<float, string>> loadDatabase(const string& fileName) {
    unordered_map<string, pair<float, string>> database;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return database;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, type;
        float value;

        getline(ss, name, ',');
        ss >> value;
        ss.ignore();
        getline(ss, type);

        database[name] = make_pair(value, type);
    }

    file.close();
    return database;
}

void updateDatabase(const string& fileName, const string& newEntry) {
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << " for updating." << endl;
        return;
    }

    file << newEntry << endl;
    file.close();
    cout << "Database updated successfully: " << newEntry << endl;
}

int main() {
    try {
        unordered_map<string, pair<float, string>> foodDB = loadDatabase("food_database.txt");
        unordered_map<string, pair<float, string>> activityDB = loadDatabase("activity_database.txt");

        cout << User::usersList.size() << " users loaded.\n";

        User user = User::inputUserInfo();

        int choice;
        do {
            cout << "\n=== Main Menu ===\n";
            cout << "1. Record Activity\n";
            cout << "2. Record Food\n";
            cout << "3. Update User Info\n";
            cout << "4. Get User Summary\n";
            cout << "5. Exit\n";
            choice = getValidInt("Enter your choice: ");

            switch (choice) {
                case 1: {
                    string activityName = getValidString("Enter activity name (lowercase): ");
                    float duration = getValidFloat("Enter duration (minutes): ");
                    float intensityMET;

                    if (activityDB.find(activityName) != activityDB.end()) {
                        intensityMET = activityDB[activityName].first;
                        cout << "MET value for " << activityName << ": " << intensityMET << " (from database)\n";
                    } else {
                        intensityMET = getValidFloat("Activity not found in the database. Enter intensity (MET): ");
                    }

                    Activity* activity = new (nothrow) Activity(activityName, duration, intensityMET, user.getWeight());
                    if (!activity) throw runtime_error("Failed to allocate memory for activity.");
                    user.recordActivity(activity);
                    break;
                }
                case 2: {
                    string foodName = getValidString("Enter food name (lowercase): ");
                    if (foodDB.find(foodName) != foodDB.end()) {
                        float caloriesPerGram = foodDB[foodName].first;
                        string foodType = foodDB[foodName].second;
                        float quantity = getValidFloat("Enter quantity (grams): ");

                        Food* food = new (nothrow) Food(foodName, caloriesPerGram, quantity, foodType);
                        if (!food) throw runtime_error("Failed to allocate memory for food.");
                        user.recordFood(food);
                    } else {
                        cout << "Food not found in the database.\n";
                        float caloriesPerGram = getValidFloat("Enter calories per gram for this food: ");
                        string foodType = getValidString("Enter food type (e.g., Protein, Carbohydrate): ");
                        float quantity = getValidFloat("Enter quantity (grams): ");

                        Food* food = new (nothrow) Food(foodName, caloriesPerGram, quantity, foodType);
                        if (!food) throw runtime_error("Failed to allocate memory for food.");
                        user.recordFood(food);

                        string newEntry = foodName + "," + to_string(caloriesPerGram) + "," + foodType;
                        updateDatabase("food_database.txt", newEntry);
                    }
                    break;
                }
                case 3:
                    user.updateUserInfo();
                    break;
                case 4:
                    user.getSummary();
                    break;
                case 5:
                    user.saveUserData("user_data.txt");
                    cout << "Exiting the program. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}

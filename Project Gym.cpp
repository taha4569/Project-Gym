

#include <iostream> // For cout, cin, endl
#include <cmath> // For round() function
#include <fstream> // For file handling
#include <ctime> // For time(0) to get the current time
#include <thread> // allows independent execution
#include <chrono> // time-related functions
#include <conio.h> // takes keyboard input
#include <string> // for string functions
#include <cstring> // for string functions
#include <limits> // for numeric_limits

using namespace std;

// Constants
const double LBS_TO_KG = 0.453592; // Conversion factor for pounds to kilograms
const double INCH_TO_CM = 2.54; // Conversion factor for inches to centimeters
const int NUM_MEALS = 10; // Number of meals per category
const int BREAKFAST = 0; // Meal categories
const int LUNCH = 1; // Meal categories
const int DINNER = 2; // Meal categories
const int NUM_CATEGORIES = 3; // Number of meal categories
const int WEIGHT_LOSS = 0; // Diet categories
const int WEIGHT_GAIN = 1; // Diet categories
const int NUM_DIETS = 2; // Number of diet categories

// This function will generate workout plans for you.
void createWorkoutPlan() {

    srand(time(0)); // Seed for randomization
    string goal, workoutSplit;
    int workoutDays = 0;

    // Array of exercises
    string exercises[7][7] = {
        {"Bench Press", "Push-ups", "Chest Fly", "Incline Bench Press", "Decline Push-ups", "Dumbbell Press", "Pec Deck Machine"},
        {"Pull-ups", "Deadlift", "Bent-over Row", "Lat Pulldown", "Seated Cable Row", "T-Bar Row", "Hyperextensions"},
        {"Squats", "Lunges", "Leg Press", "Deadlift", "Calf Raises", "Leg Extensions", "Hamstring Curls"},
        {"Shoulder Press", "Lateral Raise", "Shrugs", "Front Raise", "Reverse Fly", "Arnold Press", "Upright Row"},
        {"Bicep Curl", "Tricep Dip", "Hammer Curl", "Tricep Extension", "Preacher Curl", "Skull Crushers", "Wrist Curls"},
        {"Plank", "Crunches", "Russian Twists", "Leg Raises", "Bicycle Crunches", "Hanging Leg Raise", "Ab Wheel Rollout"},
        {"Rest", "Yoga", "Light Jogging", "Swimming", "Cycling", "Walking", "Stretching"}
    };

    string muscleGroups[7] = { "Chest", "Back", "Legs", "Shoulders", "Arms", "Core", "Recovery" }; // Array of muscle groups

    int numExercises = 7; // Number of exercises per muscle group
    int goalChoice, workoutSplitChoice = 0;

    cout << "Welcome to the Workout Planner!\nPlease enter your preferences to generate a personalized workout plan.\n\n";

    bool usedExercises[7][7] = { false }; // Tracker for used exercises
    int lastRecoveryActivityIndex = -1; // Index of the last recovery activity
    int totalExercisesPerDay = 0; // Total number of exercises per day

    // User input for fitness goal with robust error handling
    while (true) {
        cout << "Enter your fitness goal (1 for strength, 2 for hypertrophy, 3 for endurance): ";
        if (cin >> goalChoice && (goalChoice >= 1 && goalChoice <= 3)) {
            break;
        }
        else {
            cout << "Invalid input. Please enter 1 for strength, 2 for hypertrophy, or 3 for endurance.\n";
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
        }
    }

    // User input for number of workout days with robust error handling
    while (true) {
        cout << "Enter the number of days you'll work out per week (3-7): ";
        if (cin >> workoutDays && (workoutDays >= 3 && workoutDays <= 7)) {
            break;
        }
        else {
            cout << "Invalid input. Please enter a number between 3 and 7.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // User input for workout split with robust error handling
    while (true) {
        cout << "Choose your workout split (1 for fullbody, 2 for upper/lower): ";
        if (cin >> workoutSplitChoice && (workoutSplitChoice == 1 || workoutSplitChoice == 2)) {
            break;
        }
        else {
            cout << "Invalid input. Please enter 1 for fullbody or 2 for upper/lower.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Adjust sets and reps based on the goal
    int sets, reps, rest = 0;

    switch (goalChoice) {
    case 1: // Strength
        sets = 5; reps = 5; rest = 120;
        break;
    case 2: // Hypertrophy
        sets = 4; reps = 8; rest = 90;
        break;
    case 3: // Endurance
        sets = 3; reps = 12; rest = 60;
        break;
    }

    if (workoutSplitChoice == 1) {
        workoutSplit = "fullbody";
    }
    else if (workoutSplitChoice == 2) {
        workoutSplit = "upper/lower";
    }

    ofstream workoutFile("workoutPlan.txt"); // Open a file to write the workout plan
    if (workoutFile.is_open()) {
        workoutFile << "Your personalized workout plan:\n";

        for (int i = 0; i < workoutDays; i++) { // Loop for each day of the week
            workoutFile << "Day " << (i + 1) << ":\n"; // Print the day number

            memset(usedExercises, false, sizeof(usedExercises)); // Reset the used exercises tracker
            totalExercisesPerDay = 0; // Reset the total number of exercises per day

            for (int j = 0; j < 6; j++) { // Loop for each muscle group
                if (totalExercisesPerDay >= 7) { // If the total number of exercises per day is 7, break out of the loop
                    break; // Break out of the loop
                }
                bool isUpper = (j == 0 || j == 1 || j == 3 || j == 4); // Check if the muscle group is upper body
                bool isLower = (j == 2); // Check if the muscle group is lower body
                int numExercisesForGroup = (isLower && workoutSplitChoice == 2 && i % 2 == 1) ? 4 : 2; // Number of exercises per muscle group

                if ((workoutSplitChoice == 1) ||
                    (workoutSplitChoice == 2 && ((isUpper && i % 2 == 0) || (isLower && i % 2 == 1)))) { // Check if the muscle group is to be worked out on this day

                    workoutFile << muscleGroups[j] << ":\n"; // Print the muscle group
                    int exercisesDone = 0; // Number of exercises done for the muscle group
                    while (exercisesDone < numExercisesForGroup && totalExercisesPerDay < 7) { // Loop until the number of exercises per muscle group is reached
                        int randomIndex = rand() % numExercises; // Generate a random index
                        if (!usedExercises[j][randomIndex]) { // Check if the exercise has not been used before
                            workoutFile << "  - " << exercises[j][randomIndex] << " - " << sets << " sets of " << reps << " reps (rest " << rest << " seconds between sets)\n"; // Print the exercise
                            usedExercises[j][randomIndex] = true; // Mark the exercise as used
                            exercisesDone++; // Increment the number of exercises done for the muscle group
                            totalExercisesPerDay++; // Increment the total number of exercises per day
                        }
                    }
                }
            }
            int recoveryActivityIndex; // Index of the recovery activity
            do {
                recoveryActivityIndex = rand() % numExercises; // Generate a random index
            } while (recoveryActivityIndex == lastRecoveryActivityIndex); // Check if the recovery activity is the same as the last one
            lastRecoveryActivityIndex = recoveryActivityIndex; // Update the last recovery activity index
            workoutFile << muscleGroups[6] << ":\n"; // Print the recovery activity
            workoutFile << "  - " << exercises[6][recoveryActivityIndex] << "\n"; // Print the recovery activity
            workoutFile << endl; // Print a new line
        }
        workoutFile.close(); // Close the file
        cout << "\nYour personalized workout plan has been saved to 'workoutPlan.txt' successfully!\n\n";
    }
    else {
        cout << "\nUnable to save the workout plan to a file.\n";
    }
}


// TDEE calculator. TDEE refers to Total Daily Energy Expenditure, a measure of how many calories you burn per day. 
int TDEEcalculator(int age, double weight, double height, char gender) {

    cout << "Welcome to the TDEE Calculator!\nPlease enter your preferences to generate a personalized TDEE plan.\n\n";
    int activity;

    cout << "Enter your activity level: \n";

    cout << "1. Sedentary (little or no exercise)\n";
    cout << "2. Light (exercise 1-3 times a week)\n";
    cout << "3. Moderate (exercise 4-5 times a week)\n";
    cout << "4. Active (hard exercise/sports 6-7 days a week)\n";
    cout << "5. Very active (very hard exercise/physical job & exercise 2x/day)\n";
    cout << "6. Extra active (hard exercise/physical job & exercise 2x/day)\n";

    while (!(cin >> activity) || activity < 1 || activity > 6) {
        cout << "Invalid input. Please enter a number between 1 and 6 for activity level: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double bmr; // basal metabolic rate

    if (gender == 'M' || gender == 'm') {
        // BMR calculation for men
        bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
    }
    else {
        // BMR calculation for women
        bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
    }

    double activityFactor;
    switch (activity) { // Assign correct activity factor
    case 1: activityFactor = 1.2; break;
    case 2: activityFactor = 1.375; break;
    case 3: activityFactor = 1.55; break;
    case 4: activityFactor = 1.725; break;
    case 5: activityFactor = 1.9; break;
    default: activityFactor = 1.2;
    }

    double tdee = bmr * activityFactor; // Calculate TDEE

    // Round off to nearest 10
    tdee = round(tdee / 10.0) * 10.0;

    cout << "\nYour Total Daily Energy Expenditure (TDEE) is approximately: " << tdee << " calories." << endl;

    return tdee;
}

// This function will generate and save a diet plan for you.
void dietPlanner(int age, double weight, double height, char gender) {
    srand(time(0)); // Seed the random number generator

    // Array of meals
    string meals[NUM_DIETS][NUM_CATEGORIES][NUM_MEALS] = {
        // Weight loss meals
        {
            // Breakfast
            {"Scrambled eggs with spinach (20.5g protein)", "Greek yogurt with fresh berries (15.0g protein)", "Wheat germ with oatmeal (18.2g protein)", "Banana with whole grain toast (14.8g protein)", "Overnight oats with fruit and nut butter (22.1g protein)", "Whole grain toast with avocado (16.4g protein)", "Chia seed pudding with sliced banana (19.7g protein)", "Smoothie with spinach, berries, and low-fat yogurt (25.3g protein)", "Whole grain cereal with almond milk (12.0g protein)", "Quinoa porridge with nuts and seeds (10.2g protein)"},
            // Lunch
            {"Lentil soup (12.8g protein)", "Garden veggie chickpea salad sandwiches (18.0g protein)", "Spicy peanut tofu Buddha bowls (20.5g protein)", "Veggie wraps (15.9g protein)", "Chicken satay salad (24.6g protein)", "Teriyaki tofu (16.9g protein)", "Mediterranean lunch box with hummus, pita, cucumber, tomato, onion, feta salad, and a side of kalamata olives (21.4g protein)", "Veggie lunch box with roasted chickpeas, fresh peppers, cucumbers, carrots, green goddess dressing, almonds (18.7g protein)", "String cheese with whole wheat crackers (9.6g protein)", "Banana with two tablespoons of peanut butter (17.2g protein)"},
            // Dinner
            {"Black Bean and Rice Enchiladas (22.1g protein)", "Zucchini Crust Pizza (16.9g protein)", "Mutton and Asparagus Sheet-Pan Dinner (19.7g protein)", "Moo Shu Mushroom Wraps (23.6g protein)", "Turkey Stroganoff with Spaghetti Squash (28.5g protein)", "Chili-Stuffed Poblano Peppers (20.5g protein)", "Pinto Bean Tostadas (17.2g protein)", "Sheet-Pan Tilapia and Vegetable Medley (25.3g protein)", "Mediterranean Turkey Skillet (19.7g protein)", "Ginger Chicken Noodle Soup (25.3g protein)"}
        },
        // Weight gain meals
        {
            // Breakfast
            {"Banana and Almond Butter Oatmeal (40.7g protein)", "Whole grain toast with peanut butter (42.8g protein)", "Scrambled eggs with spinach and tomatoes (45.5g protein)", "Overnight oats with fruit and nut butter (56.1g protein)", "Greek yogurt with fresh berries (30.0g protein)", "Wheat germ with oatmeal (18.2g protein)", "Banana with whole grain toast (14.8g protein)", "Chia seed pudding with sliced banana (31.7g protein)", "Smoothie with spinach, berries, and low-fat yogurt (25.3g protein)", "Whole grain cereal with almond milk (36.0g protein)"},
            // Lunch
            {"Lentil soup (12.8g protein)", "Garden veggie chickpea salad sandwiches (18.0g protein)", "Spicy peanut tofu Buddha bowls (20.5g protein)", "Veggie wraps (15.9g protein)", "Chicken satay salad (24.6g protein)", "Teriyaki tofu (16.9g protein)", "Mediterranean lunch box with hummus, pita, cucumber, tomato, onion, feta salad, and a side of kalamata olives (21.4g protein)", "Veggie lunch box with roasted chickpeas, fresh peppers, cucumbers, carrots, green goddess dressing, almonds (18.7g protein)", "String cheese with whole wheat crackers (67.6g protein)", "Mass gainer protein shake (46.2g protein)"},
            // Dinner
            {"Baked Chicken Thighs With Sweet Potato And Vegetables (62.2g protein)", "Beef Stroganoff w/ Egg Noodles And Mushrooms (54.6g protein)", "Spaghetti with Turkey Meatballs and Whole Wheat Pasta (39.6g protein)", "Grilled Steak with Potato + Vegetable (65.9g protein)", "Baked Salmon with Rice Pilaf + Asparagus (43.3g protein)", "Black Bean and Rice Enchiladas (43.1g protein)", "Zucchini Crust Pizza (16.9g protein)", "Pork and Asparagus Sheet-Pan Dinner (19.7g protein)", "Moo Shu Mushroom Wraps (53.6g protein)", "Turkey Stroganoff with Spaghetti Squash (65.5g protein)"}
        }
    };

    cout << "Welcome to the Diet Planner!\nPlease enter your preferences to generate a personalized diet plan.\n\n";
    // Open a file to write the diet plan
    ofstream dietPlanFile("diet_plan.txt");

    // Get diet preference from user
    int diet;
    do {
        cout << "Enter your diet preference (0 for weight loss, 1 for muscle gain): ";
        if (!(cin >> diet) || diet < 0 || diet >= NUM_DIETS) {
            cout << "Invalid diet preference. Please enter a number between 0 and " << NUM_DIETS - 1 << ".\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        }
    } while (diet < 0 || diet >= NUM_DIETS);

    char knowsTDEE;
    double tdee;

    double minTDEE, maxTDEE;

    if (gender == 'm' || gender == 'M') {
        minTDEE = 1500; // Minimum TDEE for men
        maxTDEE = 4500; // Maximum TDEE for extremely active men
    }
    else {
        minTDEE = 1200; // Minimum TDEE for women
        maxTDEE = 4000; // Maximum TDEE for extremely active women
    }

    cout << "Do you know your Total Daily Energy Expenditure (TDEE)? (Y/N): ";
    cin >> knowsTDEE;
    knowsTDEE = toupper(knowsTDEE);

    while (knowsTDEE != 'Y' && knowsTDEE != 'N') {
        cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        cin >> knowsTDEE;
        knowsTDEE = toupper(knowsTDEE);
    }

    if (knowsTDEE == 'Y') {
        cout << "Please enter your Total Daily Energy Expenditure (TDEE) in calories: ";
        while (!(cin >> tdee) || tdee < minTDEE || tdee > maxTDEE) {
            cout << "Invalid input. Please enter a value between " << minTDEE << " and " << maxTDEE << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        cout << "Let's calculate your TDEE.\n";
        tdee = TDEEcalculator(age, weight, height, gender);
        cout << "Your TDEE is: " << tdee << " calories.\n";
    }

    // Calculate macronutrient intake
    double protein = tdee * 0.30 / 4; // 30% of TDEE for protein
    double fats = tdee * 0.25 / 9;    // 25% of TDEE for fats
    double carbs = tdee * 0.45 / 4;   // 45% of TDEE for carbs

    dietPlanFile << "Your daily macronutrient intake should be approximately:\n";
    dietPlanFile << "Protein: " << round(protein) << " grams\n";
    dietPlanFile << "Fats: " << round(fats) << " grams\n";
    dietPlanFile << "Carbohydrates: " << round(carbs) << " grams\n";

    // Print meal plan
    for (int day = 0; day < 7; ++day) {
        dietPlanFile << "\nDay " << day + 1 << ":\n";
        for (int category = 0; category < NUM_CATEGORIES; ++category) {
            int mealIndex = rand() % NUM_MEALS;
            switch (category) {
            case BREAKFAST:
                dietPlanFile << "Breakfast: ";
                break;
            case LUNCH:
                dietPlanFile << "Lunch: ";
                break;
            case DINNER:
                dietPlanFile << "Dinner: ";
                break;
            }
            dietPlanFile << meals[diet][category][mealIndex] << endl;
        }
    }

    // Close the file
    dietPlanFile.close(); // Close the file

    cout << "\nYour diet plan has been saved to 'diet_plan.txt'.\n";
}

// This function will basicallly tell you how much protein you need to consume daily (depending on your goals).
void proteinCalculator(char gender, int age, double weight, double height) {

    cout << "Welcome to the Protein Calculator!\nPlease enter your preferences to generate a personalized protein intake plan.\n\n";

    int activity;
    char goal, bodyType, diet;
    double goalWeight;

    cout << "Enter your activity level: \n";
    cout << "1. Sedentary (little or no exercise)\n";
    cout << "2. Light (exercise 1-3 times a week)\n";
    cout << "3. Moderate (exercise 4-5 times a week)\n";
    cout << "4. Active (hard exercise/sports 6-7 days a week)\n";
    cout << "5. Very active (very hard exercise/physical job & exercise 2x/day)\n";
    cout << "6. Extra active (hard exercise/physical job & exercise 2x/day)\n";
    while (!(cin >> activity) || activity < 1 || activity > 6) {
        cout << "Invalid input. Please enter a number between 1 and 6 for activity level: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
    }

    cout << "Enter your goal (G for muscle gain, M for body maintenance): ";
    cin >> goal;
    goal = tolower(goal);
    while (goal != 'g' && goal != 'm') {
        cout << "Invalid input. Please enter G for muscle gain or M for body maintenance: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        cin >> goal;
        goal = tolower(goal);
    }

    cout << "Enter your body type (E for ectomorph, M for mesomorph, N for endomorph): ";
    cin >> bodyType;
    bodyType = tolower(bodyType);
    while (bodyType != 'e' && bodyType != 'm' && bodyType != 'n') {
        cout << "Invalid input. Please enter E for ectomorph, M for mesomorph, or N for endomorph: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        cin >> bodyType;
        bodyType = tolower(bodyType);
    }

    cout << "Enter your goal weight (in kg): ";
    cin >> goalWeight;

    double minHeightMeters = height / 100.0; // assuming height is in cm
    double minWeight = 18.5 * minHeightMeters * minHeightMeters; // BMI 18.5 for minimum healthy weight
    double maxWeight = 30.0 * minHeightMeters * minHeightMeters; // BMI 30 for maximum healthy weight

    while (goalWeight <= minWeight || goalWeight >= maxWeight) {
        cout << "Invalid input. Please enter a weight between " << minWeight << " kg and " << maxWeight << " kg based on your height: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        cin >> goalWeight;
    }

    cout << "Enter your dietary restrictions (N for none, V for vegetarian, G for gluten-free): ";
    cin >> diet;
    diet = tolower(diet);
    while (diet != 'n' && diet != 'v' && diet != 'g') {
        cout << "Invalid input. Please enter N for none, V for vegetarian, or G for gluten-free: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        cin >> diet;
        diet = tolower(diet);
    }

    double protein = 0.0;

    if (gender == 'm' || gender == 'M') {
        protein = weight * 1.0; // Adjusted for men
    }
    else {
        protein = weight * 0.8; // Adjusted for women
    }
    switch (activity) { // Assign correct activity factor
    case 1:
        break;
    case 2:
        protein *= 1.1;
        break;
    case 3:
        protein *= 1.3;
        break;
    case 4:
        protein *= 1.5;
        break;
    case 5:
        protein *= 1.7;
        break;
    case 6:
        protein *= 1.9;
        break;
    }

    if (goal == 'g') {
        protein *= 1.5;
    }

    if (bodyType == 'e') {
        protein *= 1.1;
    }
    else if (bodyType == 'm') {
        protein *= 1.2;
    }
    else if (bodyType == 'n') {
        protein *= 1.3;
    }
    if (goalWeight > weight) {
        protein *= 1.2;
    }
    if (diet == 'v') {
        protein *= 1.1;
    }
    else if (diet == 'g') {
        protein *= 1.05;
    }

    protein = round(protein / 10.0) * 10.0; // Round off to the nearest tenth
    cout << "According to your preference, your daily protein intake should be approximately: " << protein << " grams." << endl;
}

// BMI calculator. We all know what this is. Body mass index.
void BMIcalculator(double weight, double height) {

    cout << "Welcome to the BMI Calculator!\n\n";

    double bmi = weight / ((height / 100) * (height / 100)); // BMI calculation

    cout << "Based on the data you provided in the start, your Body Mass Index (BMI) is: " << bmi << endl;

    if (bmi < 18.5)
        cout << "You are underweight." << endl;
    else if (bmi >= 18.5 && bmi < 24.9)
        cout << "You are at a healthy weight!" << endl;
    else if (bmi >= 25 && bmi < 29.9)
        cout << "You are overweight." << endl;
    else
        cout << "You are obese." << endl;
}

// Function to calculate and display calories burned
void calorieCalculator(int age, double weight, double height, char gender) {
    const int MinDuration = 1; // 1 minute
    const int MaxDuration = 300; // 300 minutes

    cout << "Welcome to the Calorie Calculator!\nPlease enter your preferences to generate a personalized calorie plan.\n\n";
    int exercise;
    double duration;

    cout << "Enter the number of the exercise you performed: \n";

    cout << "1. Running\n";
    cout << "2. Jogging\n";
    cout << "3. Swimming\n";
    cout << "4. Cycling\n";
    cout << "5. Walking\n";
    cout << "6. Hiking\n";
    cout << "7. Dancing\n";
    cout << "8. Aerobics\n";
    cout << "9. Yoga\n";
    cout << "10. Pilates\n";
    cout << "11. Basketball\n";
    cout << "12. Soccer\n";
    cout << "13. Tennis\n";
    cout << "14. Volleyball\n";
    cout << "15. Golf\n";
    cout << "16. Skiing\n";
    cout << "17. Rowing\n";
    cout << "18. Boxing\n";
    cout << "19. Jumping rope\n";
    cout << "20. Weightlifting\n";
    cout << "21. Stair climbing\n";
    cout << "22. Push ups\n";
    cout << "23. Sit ups\n";
    cout << "24. Squats\n";
    cout << "25. Lunges\n";
    cout << "26. Pull ups\n";
    cout << "27. Bench press\n";
    cout << "28. Deadlift\n";
    cout << "29. Leg press\n";
    cout << "30. Shoulder press\n";
    cout << "31. Lat pull down\n";
    cout << "32. Pec deck fly\n";
    cout << "33. Leg extension\n";
    cout << "34. Leg curl\n";
    cout << "35. Tricep pushdown\n";

    while (!(cin >> exercise) || exercise < 1 || exercise > 35) {
        cout << "Invalid input. Please enter a number between 1 and 35: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
    }

    cout << "Enter the duration of the exercise (in minutes): ";
    while (!(cin >> duration) || duration < MinDuration || duration > MaxDuration) {
        cout << "Invalid duration. Please enter a duration between " << MinDuration << " and " << MaxDuration << " minutes: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
    }

    double met = 0.0;

    // Assign correct MET (metabolic equivalent of task) values

    switch (exercise) {
    case 1: met = 9.8; break; // running
    case 2: met = 7.0; break; // jogging
    case 3: met = 5.8; break; // swimming
    case 4: met = 7.5; break; // cycling
    case 5: met = 3.9; break; // walking
    case 6: met = 6.0; break; // hiking
    case 7: met = 4.8; break; // dancing
    case 8: met = 5.2; break; // aerobics
    case 9: met = 2.5; break; // yoga
    case 10: met = 3.0; break; // pilates
    case 11: met = 6.5; break; // basketball
    case 12: met = 7.0; break; // soccer
    case 13: met = 7.3; break; // tennis
    case 14: met = 2.5; break; // volleyball
    case 15: met = 4.8; break; // golf
    case 16: met = 7.0; break; // skiing
    case 17: met = 7.0; break; // rowing
    case 18: met = 12.8; break; // boxing
    case 19: met = 12.3; break; // jumping rope
    case 20: met = 3.5; break; // weightlifting
    case 21: met = 4.0; break; // stair climbing
    case 22: met = 3.8; break; // push ups
    case 23: met = 3.8; break; // sit ups
    case 24: met = 2.8; break; // squats
    case 25: met = 2.8; break; // lunges
    case 26: met = 5.0; break; // pull ups
    case 27: met = 3.5; break; // bench press
    case 28: met = 3.5; break; // deadlift
    case 29: met = 3.5; break; // leg press
    case 30: met = 3.5; break; // shoulder press
    case 31: met = 3.5; break; // lat pull down
    case 32: met = 3.5; break; // pec deck fly
    case 33: met = 3.5; break; // leg extension
    case 34: met = 3.5; break; // leg curl
    case 35: met = 3.5; break; // tricep pushdown
    }

    double calories = 0.0175 * met * weight * duration; // Calculate calories burned

    // Round to nearest 10
    calories = round(calories / 10.0) * 10.0;

    cout << "You burned approximately: " << calories << " calories with an uncertainty of 10 calories." << endl;

}

// Body fat calculator. Based on the famous US Navy formula.
void bodyfatCalculator(char gender, double weight, double height) {
    // Convert height from centimeters to meters for BMI calculation
    height = height / 100.0;

    // Calculate BMI
    double calcFactor = weight / pow(height, 2);

    // Estimate Body Fat Percentage based on BMI, gender, and a constant adjustment factor
    double bodyFatPercentage;
    if (gender == 'M' || gender == 'm') {
        // For males
        bodyFatPercentage = (1.20 * calcFactor) + (0.23 * 25) - 16.2; // Assuming age 25 as age is not provided
    }
    else {
        // For females
        bodyFatPercentage = (1.20 * calcFactor) + (0.23 * 25) - 5.4; // Assuming age 25 as age is not provided
    }

    // Round body fat percentage to the nearest decimal
    bodyFatPercentage = round(bodyFatPercentage * 10) / 10; // Round to the nearest decimal

    cout << "Estimated Body Fat Percentage: " << bodyFatPercentage << "%" << endl;
}

// Stopwatch function. You can pause this too. Inspiration from https://www.thecrazyprogrammer.com/2013/06/cc-program-to-create-digital-stopwatch.html
// and other websites.
void runStopwatch() {
    cout << "Press ENTER to start the stopwatch...\n";
    cin.get();

    cout << "You can pause the stopwatch by pressing 'P', and stop it by pressing the spacebar.\n";
    cin.get();

    for (int seconds = 0; ; seconds++) { // this is basically an infinite loop

        if (_kbhit()) {  // Check if a key has been pressed

            char ch = _getch(); // Catch the pressed key into a variable


            if (ch == ' ') { // Check if the spacebar was pressed
                break;  // Breaks the loop if spacebar is pressed
            }
            // Check if 'P' was pressed
            else if (ch == 'P' || ch == 'p') { // Check if P was pressed. If yes, the stopwatch will be paused.
                cout << "\nStopwatch paused. Press any key to continue.\n";
                _getch();
                cout << "Resuming stopwatch...\n";
            }
        }

        cout << "\rElapsed time: " << seconds << " seconds";
        cout.flush(); // this makes sure the output is displayed asap


        this_thread::sleep_for(chrono::seconds(1)); // makes the code "sleep" for one second
    }

    cout << "\nStopwatch stopped." << endl;
}

// Timer function. Self-explanatory. Again, inspiration from https://www.thecrazyprogrammer.com/2013/06/cc-program-to-create-digital-stopwatch.html
// and other websites.
void runTimer() {
    const int MaxMinutes = 300; // 5 hours

    int minutes, seconds;
    bool validInput = false;

    // Input validation for minutes
    do {
        cout << "Enter time in minutes (0 to " << MaxMinutes << "): ";
        if (!(cin >> minutes) || minutes < 0 || minutes > MaxMinutes) {
            cout << "Invalid input for minutes. Please enter a number between 0 and " << MaxMinutes << ".\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    validInput = false; // Reset the flag for seconds validation

    // Input validation for seconds
    do {
        cout << "Enter time in seconds (0 to 59): ";
        if (!(cin >> seconds) || seconds < 0 || seconds >= 60) {
            cout << "Invalid input for seconds. Please enter a number between 0 and 59.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    int total_seconds = minutes * 60 + seconds; // this converts the minutes to seconds and adds the seconds

    while (total_seconds >= 0) {
        cout << "\rSeconds left: " << total_seconds << "    "; // Overwrite the entire line
        cout.flush(); // Ensures that the output is printed to the screen
        this_thread::sleep_for(chrono::seconds(1)); // Makes the code "sleep" for one second
        total_seconds--; // Decrement the total seconds
    }

    cout << "\nTime's up!" << endl; // will be printed after the loop is done running
}


// Interval function. Kind of like an advanced timer for HIIT (high intensity interval training) workout circuits. Took some assistance for this.
void runInterval() {
    int numIntervals; // number of intervals
    int workoutTime, restTime; // workout and rest times

    cout << "Enter your interval type: \n1. 10/20 intervals \n2. 30/90 intervals\n"; // 10/20 is 10 seconds workout, 20 seconds rest
    int intervalChoice; // interval choice
    while (true) { // this is basically an infinite loop
        if (cin >> intervalChoice) { // if the input is a number
            if (intervalChoice == 1) { // if the input is 1
                workoutTime = 10;
                restTime = 20;
                break;
            }
            else if (intervalChoice == 2) {
                workoutTime = 30;
                restTime = 90;
                break;
            }
            else {
                cout << "Invalid choice. Please choose 1 or 2.\n";
            }
        }
        else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        }
    }

    const int MaxIntervals = 50;
    cout << "Enter number of intervals (1 to " << MaxIntervals << "): ";
    while (true) {
        if (cin >> numIntervals) {
            if (numIntervals > 0 && numIntervals <= MaxIntervals) {
                break;
            }
            else {
                cout << "Invalid number of intervals. Please enter a positive number between 1 and " << MaxIntervals << ".\n";
            }
        }
        else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
        }
    }

    for (int i = 0; i < numIntervals; i++) { // this is basically an infinite loop
        cout << "Workout interval " << (i + 1) << " starts now!\n"; // this is the workout interval
        for (int j = workoutTime; j > 0; j--) { // this is basically an infinite loop
            cout << "\rWorkout time left: " << j << " second"; // the /r moves the cursor to the beginning of the line
            if (j > 1) cout << "s"; // plural
            cout.flush(); // ensures that the output is printed to the screen
            this_thread::sleep_for(chrono::seconds(1)); // makes the code "sleep" for one second
        }

        cout << "\nRest interval " << (i + 1) << " starts now!\n"; // this is the rest interval
        for (int j = restTime; j > 0; j--) { // this is basically an infinite loop
            cout << "\rRest time left: " << j << " second"; // the /r moves the cursor to the beginning of the line
            if (j > 1) cout << "s"; // plural
            cout.flush(); // ensures that the output is printed to the screen
            this_thread::sleep_for(chrono::seconds(1)); // makes the code "sleep" for one second
        }
    }

    cout << "\nInterval workout completed!" << endl; // will be printed after the loop is done running
}

// Main function
int main() {
    // Initialize variables
    char gender = 'M';
    int age = 0;
    double weight, height = 0.0;
    char weightUnit, heightUnit;

    // Initialize constants, along with reasonable limit constants
    const int MinAge = 13;
    const int MaxAge = 65;
    const double MinWeight = 20.0; // 20 kg
    const double MaxWeight = 200.0; // 200 kg
    const double MinWeightKg = 40.0; // 40 kg
    const double MaxWeightKg = 200.0; // 200 kg
    const double MinHeightCm = 140.0; // 140 cm
    const double MaxHeightCm = 210.0; // 210 cm

    // Ask for user details once at the beginning
    cout << "Welcome to Project Gym! Let's start with some basic information :)\n";

    // Age input and validation
    while (true) {
        cout << "Enter your age: ";
        cin >> age;

        if (cin.fail() || cin.peek() != '\n' || age < 0) { // cin.peek() checks if the next character is a newline
            cout << "Invalid input. Please enter a whole number for age.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
            continue;
        }

        if (age < 13 || age > 65) {
            cout << "Sorry, this program is designed for individuals between the ages of 13 and 65.\n"
                << "This is to ensure the safety and appropriateness of the health advice provided,\n"
                << "as younger and older individuals may have different health and fitness needs that require specialized attention.\n";
            exit(0); // Program terminates if the age is not between 13 and 65
        }
        break;
    }

    // Gender input and validation
    while (true) {
        cout << "Enter your gender (M for male, F for female): ";
        cin >> gender;
        if (cin.fail() || cin.get() != '\n') {
            cout << "Invalid input. Please enter a single character ('M' or 'F').\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue;
        }
        gender = toupper(gender); // Convert to uppercase
        if (gender == 'M' || gender == 'F') {
            break;
        }
        cout << "Invalid gender entered. Please enter 'M' or 'F'.\n";
    }

    // Weight unit input and validation
    while (true) {
        cout << "Enter the unit for weight (k for kilograms or l for pounds): ";
        cin >> weightUnit;
        if (cin.fail() || cin.get() != '\n') {
            cout << "Invalid input. Please enter a single character ('k' or 'l').\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue;
        }
        weightUnit = tolower(weightUnit);
        if (weightUnit == 'k' || weightUnit == 'l') {
            break;
        }
        cout << "Invalid unit. Please enter 'k' or 'l'.\n";
    }

    // Weight input and validation
    while (true) {
        cout << "Enter your weight: ";
        cin >> weight;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (tolower(weightUnit) == 'l') {
            weight *= LBS_TO_KG;
        }

        if (weight <= 0 || weight < MinWeightKg || weight > MaxWeightKg) {
            cout << "Invalid weight. Please enter a reasonable weight estimate.\n";
            continue;
        }
        break;
    }

    // Height unit input and validation
    while (true) {
        cout << "Enter the unit for height (c for centimeters or i for inches): ";
        cin >> heightUnit;
        if (cin.fail() || cin.get() != '\n') {
            cout << "Invalid input. Please enter a single character ('c' or 'i').\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue;
        }
        heightUnit = tolower(heightUnit);
        if (heightUnit == 'c' || heightUnit == 'i') {
            break;
        }
        cout << "Invalid unit. Please enter 'c' or 'i'.\n";
    }

    // Height input and validation
    while (true) {
        cout << "Enter your height: ";
        cin >> height;

        if (cin.fail()) {
            // Handle non-numeric input
            cout << "Invalid input. Please enter a positive number.\n";
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
            continue;
        }

        if (tolower(heightUnit) == 'i') {
            // Convert inches to centimeters
            height *= INCH_TO_CM;
        }

        if (height <= 0 || height < MinHeightCm || height > MaxHeightCm) {
            // Check if the height is within the valid range
            cout << "Invalid height. Please enter a reasonable height estimate.\n";
            continue;
        }
        break;
    }


    int userChoice = 0;
    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Generate a personalized workout plan\n";
        cout << "2. Generate and save a diet plan\n";
        cout << "3. Calculate required protein intake for my goals\n";
        cout << "4. Calculate my BMI\n";
        cout << "5. Calculate total calories burned\n";
        cout << "6. Calculate my TDEE (Total Daily Energy Expenditure)\n";
        cout << "7. Calculate my body fat percentage\n";
        cout << "8. Run a stopwatch\n";
        cout << "9. Run a timer\n";
        cout << "10. Run intervals for HIIT (High-Intensity Interval Training)\n";
        cout << "11. Exit\n";
        cout << endl;

        if (!(cin >> userChoice)) {
            cout << "Invalid input. Please enter a valid number between 1 and 11.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the incorrect input
            continue;
        }

        switch (userChoice) {
        case 1:
            createWorkoutPlan(); // Call the function to create a workout plan
            break;
        case 2:
            dietPlanner(age, weight, height, gender); // Call the function to create a diet plan
            break;
        case 3:
            proteinCalculator(gender, age, weight, height); // Call the function to calculate protein intake
            break;
        case 4:
            BMIcalculator(weight, height); // Call the function to calculate BMI
            break;
        case 5:
            calorieCalculator(age, weight, height, gender); // Call the function to calculate calories burned
            break;
        case 6:
            TDEEcalculator(age, weight, height, gender); // Call the function to calculate TDEE
            break;
        case 7:
            bodyfatCalculator(gender, weight, height); // Call the function to calculate body fat percentage
            break;
        case 8:
            runStopwatch(); // Call the function to run a stopwatch
            break;
        case 9:
            runTimer(); // Call the function to run a timer
            break;
        case 10:
            runInterval(); // Call the function to run intervals
            break;
        case 11:
            cout << "Exiting the program. Have a great day!\n"; // Exit the program
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 11.\n"; // If the user enters a number other than 1-11
            break;
        }
    }
    return 0;
} 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


void exchangeCoinsBruteForce(int coins[], int numCoins, int amount) {
    int dp[amount + 1];
    int usedCoins[amount + 1];
    dp[0] = 0;
    usedCoins[0] = -1;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
        usedCoins[i] = -1;
    }

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < numCoins; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX && dp[i - coins[j]] + 1 < dp[i]) {
                dp[i] = dp[i - coins[j]] + 1;
                usedCoins[i] = j; // Simpan index koin yang digunakan
            }
        }
    }

    if (dp[amount] == INT_MAX) {
        printf("No solution found for amount %d\n", amount);
    } else {
        printf("Minimum coins needed: %d\n", dp[amount]);
        printf("Coin combination: ");
        int remain = amount;
        while (remain > 0) {
            printf("%d ", coins[usedCoins[remain]]);
            remain -= coins[usedCoins[remain]];
        }
        printf("\n");
    }
}

void exchangeCoinsGreedy(int coins[], int numCoins, int amount) {
    // Sort secara descending
    for (int i = 0; i < numCoins - 1; i++) {
        for (int j = 0; j < numCoins - i - 1; j++) {
            if (coins[j] < coins[j + 1]) {
                int temp = coins[j];
                coins[j] = coins[j + 1];
                coins[j + 1] = temp;
            }
        }
    }

    int count = 0;
    int usedCoins[1000];

    for (int i = 0; i < numCoins; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            count++;
            usedCoins[count - 1] = coins[i]; // Simpan koin yang digunakan
        }
    }

    if (amount == 0) {
        printf("Minimum coins needed: %d\n", count);
        printf("Coin combination: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", usedCoins[i]);
        }
        printf("\n");
    } else {
        printf("No solution found for amount %d\n", amount);
    }
}


struct Job {
    char id[20];
    int deadline;
};

int compareJobs(const void *a, const void *b) {
    return ((struct Job *)a)->deadline - ((struct Job *)b)->deadline;
}

void jobSchedulingBruteForce(struct Job *task, int n) {
    int total = 0, i, j;
    for (i = 0; i < n; i++) {
        int sum = 0;
        for (j = 0; j < n; j++) {
            if (i != j) {
                sum += task[j].deadline;
            }
        }
        if (total == 0 || sum < total) {
            total = sum;
        }
    }

    qsort(task, n, sizeof(struct Job), compareJobs);
    printf("\nTasks that have been sorted by duration:\n");
    for (i = 0; i < n; i++) {
        printf("%s ", task[i].id);
    }
    printf("\n");
    printf("Total waiting time: %d\n", total);
}

void jobSchedulingGreedy(struct Job *task, int n) {
    int total = 0, i;
    qsort(task, n, sizeof(struct Job), compareJobs);
    for (i = 0; i < n - 1; i++) {
        total += task[i].deadline;
    }

    printf("\nTasks that have been sorted by duration:\n");
    for (i = 0; i < n; i++) {
        printf("%s ", task[i].id);
    }

    printf("Total waiting time: %d\n", total);
}

void knapsackProblemBruteForce(int capacity, int weight[], int value[], int n) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weight[i - 1] <= w) {
                dp[i][w] = fmax(value[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("(Brute Force) : %d\n", dp[n][capacity]);
}

void knapsackProblemGreedyByProfit(int capacity, int weight[], int value[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)value[i] < (double)value[j]) {
                int temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;
                temp = value[i];
                value[i] = value[j];
                value[j] = temp;
            }
        }
    }

    int maxProfit = 0, weightTemp = 0;
    for (int i = 0; i < n; i++) {
        if (weightTemp + weight[i] <= capacity) {
            weightTemp += weight[i];
            maxProfit += value[i];
        }
    }
    printf("(Greedy by Profit) : %d\n", maxProfit);
}

void knapsackProblemGreedyByWeight(int capacity, int weight[], int value[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (weight[i] > weight[j]) {
                int temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;
                temp = value[i];
                value[i] = value[j];
                value[j] = temp;
            }
        }
    }

    int maxValue = 0, weightTemp = 0;
    for (int i = 0; i < n; i++) {
        if (weightTemp + weight[i] <= capacity) {
            weightTemp += weight[i];
            maxValue += value[i];
        }
    }
    printf(" (Greedy by Weight) : %d\n", maxValue);
}

void knapsackProblemGreedyByDensity(int capacity, int weight[], int value[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)value[i] / weight[i] < (double)value[j] / weight[j]) {
                int temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;
                temp = value[i];
                value[i] = value[j];
                value[j] = temp;
            }
        }
    }

    int maxValue = 0, weightTemp = 0;
    for (int i = 0; i < n; i++) {
        if (weightTemp + weight[i] <= capacity) {
            weightTemp += weight[i];
            maxValue += value[i];
        }
    }
    printf("(Greedy by Density) : %d\n", maxValue);
}

int main() {
    int choice;
    
    do {
        printf("Menu:\n");
        printf("1. Exchange Coins\n");
        printf("2. Job Scheduling\n");
        printf("3. Knapsack Problem\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            int numCoins, amount, method;
            printf("Enter the number of coins: ");
            scanf("%d", &numCoins);
            int coins[numCoins];
            printf("Enter the values of coins: ");
            for(int i = 0; i < numCoins; i++) {
                scanf("%d", &coins[i]);
            }
            printf("Enter the amount of money to be exchanged: ");
            scanf("%d", &amount);
            printf("Choose Method:\n1. Brute Force\n2. Greedy\nEnter your choice: ");  
            scanf("%d", &method);

            if(method == 1) {
                exchangeCoinsBruteForce(coins, numCoins, amount);
            } else if(method == 2) {
                exchangeCoinsGreedy(coins, numCoins, amount);
            }
        } else if(choice == 2) {
            int n;
            printf("Enter the number of task: ");
            scanf("%d", &n);

            struct Job task[n];
            
            for (int i = 0; i < n; i++) {
                printf("Enter the name and deadline of task %d (format: name deadline): ", i + 1);
                scanf("%s %d", task[i].id, &task[i].deadline);
            }

            int method;
            printf("Choose Method:\n1. Brute Force\n2. Greedy\nEnter your choice: ");
            scanf("%d", &method);

            if(method == 1) {
                jobSchedulingBruteForce(task, n);
            } else if(method == 2) {
                jobSchedulingGreedy(task, n);
            }
        } else if(choice == 3) {
            int capacity;
            printf("Enter the capacity of knapsack: ");
            scanf("%d", &capacity);

            int n;
            printf("Enter the number of items: ");
            scanf("%d", &n);

            int weight[n], value[n];
            printf("Enter the values and weight of items:\n");
            for (int i = 0; i < n; i++) {
                scanf("%d %d", &value[i], &weight[i]);
            }

            int method;
            printf("Choose Method\n1. Brute Force\n2. Greedy by Profit\n3. Greedy by Weight\n4. Greedy by Density\nEnter your choice: ");
            scanf("%d", &method);

            if(method == 1) {
                knapsackProblemBruteForce(capacity, weight, value, n);
            } else if(method == 2) {
                knapsackProblemGreedyByProfit(capacity, weight, value, n);
            } else if(method == 3) {
                knapsackProblemGreedyByWeight(capacity, weight, value, n);
            } else if(method == 4) {
                knapsackProblemGreedyByDensity(capacity, weight, value, n);
            }
        }
    } while(choice != 4);

    return 0;
}
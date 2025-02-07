# Console-based Social Network Application

## Overview
This project is a console-based social network application that simulates basic social media functionalities. Users can have friends, like pages, share posts, comment on posts, and interact with other users' content. The application is implemented in C++ and follows object-oriented programming (OOP) principles.

## Features

#### **1. Set Current User**
   - Allows setting a user as the current active user.

#### **2. View Home of Current User**
   - Displays posts from friends and liked pages shared in the last 24 hours.

#### **3. Like a Post**
   - Enables a user to like a post.

#### **4. View the List of People Who Liked a Post**
   - Shows users who have liked a specific post.

#### **5. Comment on a Post**
   - Users can add comments to posts.

#### **6. View a Post**
   - Displays a post along with its comments.

#### **7. Share a Memory**
   - Allows users to share an old post as a memory with additional text.

#### **8. View User’s Timeline**
   - Shows a user’s name and all posts they have shared.

#### **9. View Friend List**
   - Displays a list of the current user's friends.

#### **10. View Page**
   - Shows posts from a specified page.

## Implementation Details
- **No global variables and functions**
- **Best OOP practices followed**
- **Memory management is handled properly**
- **Dynamic arrays are used**
- **Double pointers are used for object arrays**
- **If a user has no friends/liked pages, the double pointer is NULL**

## Sample Run
The program executes hardcoded commands without taking user input. Example outputs:
```
Command: Set current System Date 15 11 2017
System Date: 15/11/2017
Command: Set current user "u7"
Abdullah Nadeem successfully set as Current User
Command: View Friend List
------------------------------------------------------------
Abdullah Nadeem – Friend List
u3 - Waheed Khan
u11 – Ahsan Ali
u12 – Ali Ahmed
------------------------------------------------------------
Command: View Home
------------------------------------------------------------
--- Waheed Khan is feeling excited
"OOP Project Started Yayy..."
Amna Akram wrote: "Best of Luck"
Abdullah Nadeem wrote: "Interesting"
------------------------------------------------------------
```

## How to Run the Application
1. **Compile the code using a C++ compiler**:
   ```sh
   g++ source.cpp -o social_network
   ```
2. **Run the compiled executable**:
   ```sh
   ./social_network
   ```

## Constraints
- No runtime input (everything is hardcoded in `main()` function).


## Developed By
- ariba-arshad


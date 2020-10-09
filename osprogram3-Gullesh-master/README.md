# Program #3

Name: Mehdi Nourelahi

How to compile all four programs:

Dining Philosophers: g++ philosophers.cpp -o philosopher -pthread --std=c++11

./philosopher

------------------------------------------------------------------

Dining Savages: g++ savages.cpp -o savage -pthread --std=c++11

./savage Nservings

second element would be the number of servings in the pot(default is 10).

-------------------------------------------------------------------------

Unisex Bathroom: g++ semaphore_mutex_unisex.cpp -o unisex -pthread --std=c++11

./unisex m f

______________________________________________________________


Physical Plant: g++ plant.cpp -o plant -pthread --std=c++11

./plant

---------------------------------------------------------------

Anything not working: No. I guess it all works great. Tried on linux machines too. all compiled.

---

grading: 47/50<BR>
problem1: 15/15<BR>
  * compiles, works until it doesn't.
  * issues
    * it's okay.

problem2: 15/15<BR>
  * compiles, works yes
  * issues

problem3: 5/5<BR>
  * added correctly? add far more then necessary.
  * still compiles and runs? yes

problem4: 12/15<BR>
  * compiles, works yes
  * issues
    * unprotected access to tchavail in if statement. -3



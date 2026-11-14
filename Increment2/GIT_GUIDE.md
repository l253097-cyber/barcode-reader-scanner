# Git steps for Increment 2 (same repo as Increment 1)

## A) Team lead (one person, once)
```
git checkout main
git pull
git checkout -b increment2          # shared Increment 2 branch
# copy this whole "Increment2" folder into the repo root (next to Increment1)
git add Increment2
git commit -m "Increment2: add full skeleton (backend + GUI + tests)"
git push -u origin increment2
```

## B) Every member (once, to receive the skeleton)
```
git fetch origin
git checkout <your-existing-branch>     # e.g. member2
git merge origin/increment2             # skeleton files now appear in VS Code
```

## C) Daily work
```
# edit ONLY the functions marked with your member number (see OWNERSHIP.md)
git add Increment2
git commit -m "Member 2: implement createOrder, addProductToOrder"
git push origin <your-branch>
```
Then open a Pull Request: <your-branch> -> increment2.
Order of merging: Models -> Managers/File handlers -> Controller -> GUI.
When everything works: increment2 -> test branch (trial) -> main.

## D) Tips
- Never edit a function owned by another member (avoids merge conflicts).
- Pull the latest increment2 before starting each work session: `git merge origin/increment2`.
- Increment1 files are NOT copied; CMake includes them from ../Increment1.

# TowerDefense

# Conventions

## Git

- before working on anything, make sure to run a `git pull` to fetch and merge any changes that have been pushed to the remote repo.

- only make changes to your **individual** branch and **never** push to any other branch.

- When staging before you commit, make sure that each resulting commit will work on its own, I.E (when checking out individual commits make sure they're not dependant on eachother).

- always put a commit message on your commit, and it must be following the [convential commits](https://www.conventionalcommits.org/en/v1.0.0/) format

- if you can't push changes due to a conflict, do **NOT** run `git push -force`. It is likely due to forgetting to run `git pull` prior and now your repo is behind the remote one, ask someone for help.

- when merging two branches, always use rebase and not merge.

## Code

### Organization 

- avoid methods with more than 15 lines, try to modularize.


### Case Types
- `camelCase` for **methods**
- `snake_case` for non-const **variables** & **filenames**
- `UPPERCASE` for **const** variables
- `PascalCase` for **classes** and **structs**

### In-file documentation

- write proper doxygen documentation for your methods.



# More to be added later, so keep checking.



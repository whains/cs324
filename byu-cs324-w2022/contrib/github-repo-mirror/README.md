# Mirroring the Class GitHub Repository

This semester many class assignments are hosted on GitHub in the following
repository:

```
https://github.com/cdeccio/byu-cs324-w2022
```

Individual assignments are in subfolders.  Within the folder for every assignment
is a `README.md` file, containing the description for the assignment.  The
folder also contains other files that are part of the assignment.  The
description of the assignment is often best viewed with a Web browser.  The
accompanying files can be downloaded directly from the folder, with a Web
browser. However, in order to more easily download files associated with
assignments, keep them up-to-date, and simultaneously version your own code
developed for class, we suggest mirroring the class GitHub repository.


## Registering an SSH Key for Use with GitHub

These steps are necessary for you to use SSH to fetch and push your updates
from and to GitHub.  They should be performed on the machine on which you will
be doing your work.  If you already have an SSH key registered with GitHub from
the machine on which you will be doing your work, then you do not need to do
this again.

 1. Find out if you already have an SSH key to use by running the following:

    ```
    $ ls -ltra ~/.ssh/id_*
    -rw-r--r-- 1 user group  564 Jan  7 15:35 /home/user/.ssh/id_rsa.pub
    -rw------- 1 user group 2635 Jan  7 15:35 /home/user/.ssh/id_rsa
    ```

    In the above example, there is a public/private key pair named `id_rsa.pub`
    and `id_rsa`, respectively.  However, if there are no keys, `ls` will
    return an error:

    ```
    $ ls -ltra ~/.ssh/id_*
    ls: cannot access '/home/user/.ssh/id_*': No such file or directory
    ```

    If you have keys then you can now to step 3.  Otherwise, continue to step 2.

 2. Run the following from the command line to create an SSH public/private key
    pair:

    ```
    $ ssh-keygen
    Generating public/private rsa key pair.
    ```

    At the following prompt, just hit enter to use the default file location:
    ```
    Enter file in which to save the key (/home/user/.ssh/id_rsa):
    ```

    Optionally enter a passphrase at the next prompt.  This makes sure that the
    private key cannot be used without the passphrase. This is good practice
    for a shared machine in particular:

    ```
    Enter passphrase (empty for no passphrase):
    Enter same passphrase again:
    ```

 3. Print the contents of your _public_ key, and copy them to your clipboard:

    ```
    $ cat ~/.ssh/id_rsa.pub
    ```
    (this assumes the name of your public key file is `id_rsa.pub`.)

 4. Follow steps 2 through 8 in the
    [official documentation](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
    to register your SSH key with your GitHub account.


## Create a Mirrored Version of the GitHub Class Repository

This is a one-time process to create and configure your own private repository
for referencing and committing changes, which repository is a mirror of the
upstream class repository.

Throughout these steps, we will refer to the official class repository as the
"upstream" repository and your own repository as the "new" repository.

 1. Create new repository on github. Follow steps 1 through 6 in the
    [official documentation](https://docs.github.com/en/get-started/quickstart/create-a-repo#create-a-repository),
    adhering to the following:
    - Create the repository under your user ("username"), and name the
      repository `byu-cs324-w2022` (Step 2).
    - Make sure the visibility of the repository is _Private_ (Step 4).
    - Do _not_ check the box "Initialize this repository with a README" (Step 5).

 2. Clone the upstream repository by running the following from the
    terminal:
    ```
    git clone --bare https://github.com/cdeccio/byu-cs324-w2022 upstream-repo
    ```

 3. Push a mirror of the upstream repository to the new repository, which you
    have just created:
    ```
    cd upstream-repo
    git push --mirror ssh://git@github.com/username/byu-cs324-w2022
    ```
    (substitute "username" with your GitHub username)

 4. Remove your clone of the upstream repository.
    ```
    cd ../
    rm -rf upstream-repo
    ```

 5. Clone your new repository, which is now a mirror of the upstream repository:
    ```
    git clone ssh://git@github.com/username/byu-cs324-w2022
    ```
    (substitute "username" with your GitHub username)

 6. Add the upstream repository to your clone:
    ```
    cd byu-cs324-w2022
    git remote add upstream ssh://git@github.com/cdeccio/byu-cs324-w2022
    git remote -v
    ```

## Update Your Mirrored Repository from the Upstream

Do this every time you would like to pull down the changes from the upstream
repository and integrate them into your own repository:

 1. Pull down the latest changes from both your repository and the upstream:
    ```
    git fetch --all
    ```
 2. Stash (save aside) any uncommitted changes that you might have locally in
    your clone:
    ```
    git stash
    ```
 3. Merge in the changes from the upstream repository:
    ```
    git merge upstream/master
    ```
 4. Merge back in any uncommitted changes that were stashed:
    ```
    git stash pop
    ```
 5. Push out the locally merged changes to your repository:
    ```
    git push
    ```

## Commit and push local changes to private repo:

Do this every time you want to commit changes to the clone of your repository
and push them out to the repository:

 1. Commit any local changes that you've made (i.e., in your own development):
    ```
    git commit ...
    ```
    (replace "..." with the names of any files or directories that have changes)
 2. Push out your local commits to your repository:
    ```
    git push
    ```

param (
    [string]$Message = "Auto commit"
)

git add .

if ($Message -eq "") {
    $Message = "Auto commit"
}

git commit -m "$Message"
git push
folder="../../data/gri_data/"
echo $1
if [ $1 ]; then
    folder=$1
fi

# shellcheck disable=SC2207
IFS=$'\n' files=( $(find "${folder}" -type f  -print) )
for file in "${files[@]}"; do
  echo "$file ....."
  ./run_paraminier_comp.sh "${file}"
done

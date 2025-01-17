var shoppingList = [ ];
function additem(item) {
    shoppingList.push(item);
    console.log("Item Added: " + item);
}
function removeitem(index) {
    if (index >= 0 && index<shoppingList.length) {
        var removeditem = shoppingList.splice(index,1);
        console.log("Item removed: " + removeditem);
    } else {
        console.log("Invalid Item Index");
    }
}
function displayitem() {
    console.log("Shopping List: ");
    for (var i = 0; i < shoppingList.length; i++) {
        console.log(i+1 + " : " + shoppingList[i]);
    }
}
function clearitem() {
    shoppingList = [];
    console.log("All Items Cleared");
}

additem("Apples");
additem("Bread");
additem("Milk");
displayitem();
removeitem(1); // Remove Bread
displayitem();
clearitem();
var tasks = [];
function addtask(task) {
    tasks.push(task);
    console.log("Task Added: " + task);
}
function removetask(index) {
    if (index >= 0 && index<tasks.length) {
        var removedtask = tasks.splice(index,1);
        console.log("Task removed: " + removedtask);
    } else {
        console.log("Invalid Task Index");
    }
}
function displaytask() {
    console.log("To-Do List: ");
    for (var i = 0; i < tasks.length; i++) {
        console.log(i+1 + " : " + tasks[i]);
    }
}
function cleartask() {
    tasks = [];
    console.log("All Tasks Cleared");
}

addtask("Competing Assignment");
addtask("Study for Quiz");
addtask("Lab Submission");

displaytask();
removetask(1);
displaytask();
cleartask();
displaytask();
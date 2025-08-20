var tasks = ["Competing Assignment", "Study for Quiz", "Lab Submission"];
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

function promptOperation() {
    let operation;
    do {
        operation = prompt("Enter the operation you want to perform (add, remove, display, clear, exit):").toLowerCase();
        
        switch(operation) {
            case 'add':
                var task = prompt("Enter the task to add:");
                addtask(task);
                break;
            case 'remove':
                var index = parseInt(prompt("Enter the task index to remove:")) - 1; // Convert to zero-based index
                removetask(index);
                break;
            case 'display':
                displaytask();
                break;
            case 'clear':
                cleartask();
                break;
            case 'exit':
                console.log("Exiting the task manager.");
                break;
            default:
                console.log("Invalid operation. Please choose add, remove, display, clear, or exit.");
        }
    } while (operation !== 'exit');
}

promptOperation();
// Selectors
const inputTask = document.getElementById('input-task');
const addButton = document.querySelector('.add-btn');
const taskList = document.getElementById('task-list');
const deleteCheckedBtn = document.querySelector('.dele-checked');
const deleteAllBtn = document.querySelector('.dele-all');

// Load tasks from local storage on page load
document.addEventListener('DOMContentLoaded', getTasksFromLocalStorage);

// Event Listeners
addButton.addEventListener('click', addTask);
inputTask.addEventListener('keypress', function (e) {
    if (e.key === 'Enter') {
        addTask();
    }
});
taskList.addEventListener('click', handleTaskAction);
deleteCheckedBtn.addEventListener('click', deleteCheckedTasks);
deleteAllBtn.addEventListener('click', deleteAllTasks);

// Function to add a new task
function addTask() {
    const taskValue = inputTask.value.trim();

    if (taskValue === '') {
        alert('Please enter a task');
        return;
    }

    // Create task element
    const taskItem = document.createElement('li');
    taskItem.innerHTML = `
        <i class="fa-regular fa-circle"></i>  ${taskValue}
        <span>&times;</span>`;
    taskList.appendChild(taskItem);

    // Save task with unchecked state to local storage
    saveTaskToLocalStorage(taskValue, false);

    // Clear the input field
    inputTask.value = '';
}

// Function to handle task actions (check/uncheck, delete)
function handleTaskAction(e) {
    const target = e.target;
    const taskItem = target.parentElement;
    const taskDescription = taskItem.childNodes[2].textContent.trim();

    // Check/uncheck task
    if (target.classList.contains('fa-circle') || target.classList.contains('fa-circle-check')) {
        target.classList.toggle('fa-circle');
        target.classList.toggle('fa-circle-check');
        taskItem.classList.toggle('checked');
        
        const isChecked = taskItem.classList.contains('checked');
        updateTaskStateInLocalStorage(taskDescription, isChecked);
    }

    // Remove task
    if (target.tagName === 'SPAN') {
        removeTaskFromLocalStorage(taskDescription);
        taskItem.remove();
    }
}

// Delete Checked Tasks
function deleteCheckedTasks() {
    const tasks = document.querySelectorAll('#task-list li');
    
    tasks.forEach(task => {
        if (task.classList.contains('checked')) {
            const taskDescription = task.childNodes[2].textContent.trim();
            removeTaskFromLocalStorage(taskDescription);
            task.remove();
        }
    });
}

// Delete All Tasks
function deleteAllTasks() {
    const tasks = document.querySelectorAll('#task-list li');
    tasks.forEach(task => task.remove());

    // Clear all tasks from local storage
    localStorage.removeItem('tasks');
}

// Save task to local storage
function saveTaskToLocalStorage(taskDescription, isChecked) {
    let tasks = getTasks();
    tasks.push({ description: taskDescription, checked: isChecked });
    localStorage.setItem('tasks', JSON.stringify(tasks));
}

// Update task checked state in local storage
function updateTaskStateInLocalStorage(taskDescription, isChecked) {
    let tasks = getTasks();
    tasks = tasks.map(task => {
        if (task.description === taskDescription) {
            return { description: taskDescription, checked: isChecked };
        }
        return task;
    });
    localStorage.setItem('tasks', JSON.stringify(tasks));
}

// Get tasks from local storage
function getTasksFromLocalStorage() {
    let tasks = getTasks();

    tasks.forEach(task => {
        const taskItem = document.createElement('li');
        taskItem.innerHTML = `
            <i class="fa-regular ${task.checked ? 'fa-circle-check' : 'fa-circle'}"></i> ${task.description}
            <span>&times;</span>`;
        if (task.checked) {
            taskItem.classList.add('checked');
        }
        taskList.appendChild(taskItem);
    });
}

// Helper function to get tasks array from local storage
function getTasks() {
    let tasks;
    if (localStorage.getItem('tasks') === null) {
        tasks = [];
    } else {
        tasks = JSON.parse(localStorage.getItem('tasks'));
    }
    return tasks;
}

// Remove task from local storage
function removeTaskFromLocalStorage(taskDescription) {
    let tasks = getTasks();
    tasks = tasks.filter(task => task.description !== taskDescription);
    localStorage.setItem('tasks', JSON.stringify(tasks));
}

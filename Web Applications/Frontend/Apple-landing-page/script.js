// IIFE (Immediately Invoked Function Expression) to avoid polluting the global scope
(function() {
    const mainImage = document.querySelector('.main-image');
    const container = document.querySelector('.container');
    const footer = document.querySelector('footer');

    // Change the main image of the page
    function changeMainImage(newImage) {
        if (newImage && newImage.src) {
            mainImage.src = newImage.src;
        }
    }

    // Change the background color of the container
    function changeBackgroundColor(color) {
        container.style.backgroundColor = color;
    }

    // Event delegation for footer images
    footer.addEventListener('click', (event) => {
        if (event.target.tagName === 'IMG') {
            changeMainImage(event.target);
            changeBackgroundColor(event.target.dataset.color);
        }
    });
})();

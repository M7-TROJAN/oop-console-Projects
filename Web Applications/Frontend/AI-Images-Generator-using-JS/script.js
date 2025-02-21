const api = "Your OpenAI API key here"; // replace with your OpenAI API key
const inp = document.getElementById("inp");
const images = document.querySelector(".images");

const getImage = async () => {
    // make a POST request to the OpenAI API
    const methods = {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
            "Authorization": `Bearer ${api}`
        },
        body: JSON.stringify({
            "prompt": inp.value,
            "n": 3,
            "size": "256x256"
        })
    };
    const res = await fetch("https://api.openai.com/v1/images/generations", methods);

    // parse the response as JSON
    const data = await res.json();
    const listImages = data.data;
    listImages.map((image) => {
        const container = document.createElement("div");
        images.appendChild(container);
        const img = document.createElement("img");
        img.src = image.url;
        container.appendChild(img);
    });
}
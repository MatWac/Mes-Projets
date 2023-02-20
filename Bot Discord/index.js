const Discord = require("discord.js");
const fetch = require("node-fetch");
var fs = require('fs');
const Client = new Discord.Client;

const prefix = "!";
const url = "https://www.openquizzdb.org/api.php?key=4XEHKP98P4";

var players = [];
var plateau = [];
var maxplayers = 1;

var reponses = [];
var reponse_correcte;
var question;
var data;
var rep;

var defi;

var score = 0;

var start = 0;
var tourplayer;
var numplayer;
var des;

var i = 0;
var e = 0;



function entierAleatoire(min, max)
{
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function dataquestion(nbr){

    reponses = [];
    var obj = JSON.parse(fs.readFileSync('A:/Discord/BDD.json', 'utf8'));
    data = obj.questions[nbr];
    question = data.question;
    reponses.push(data.propositions[0]);
    reponses.push(data.propositions[1]);
    reponses.push(data.propositions[2]);
    reponses.push(data.propositions[3]);
    reponse_correcte = data.réponse;
    anecdote = data.anecdote;
}

const messageentree = "**Bonjour à tous 👋 👋  Commençons à jouer !** 🎲";
const messageajout = "Réagissez  ✅ pour ajouter des joueurs ! \nMinimum " + maxplayers + " joueurs pour commencer";
const messagequestion = "⚠️ Attention ! Les 2 questions arrivent ! ⚠️";


Client.on("ready", () => {

    console.log("Bot Online");
    Client.channels.cache.find(channel => channel.id === "829369159354941461").bulkDelete(100);
    Client.channels.cache.find(channel => channel.id === "829369159354941461").bulkDelete(100);
    Client.channels.cache.find(channel => channel.id === "829369159354941461").bulkDelete(100);
    Client.channels.cache.find(channel => channel.id === "829369159354941461").bulkDelete(100);
    Client.channels.cache.find(channel => channel.id === "829369159354941461").send({files: ["A:/Discord/Logo.jpg"]});
    Client.channels.cache.find(channel => channel.id === "829369159354941461").send(messageentree);

});

Client.on("guildMemberAdd", member =>{

    member.roles.add("825483557953601557");
})


Client.on("message", msg =>{

    //Message de début
    if(msg.content === messageentree)
    {
        msg.channel.send(messageajout);
    }   

    //Reaction pour l'ajout des joueurs
    if(msg.channel.lastMessage.content.includes(messageajout))
    {
        msg.react("✅");         
    }

    //Début du tour d'un joueur
    if(start === 1){

        if(i >= players.length && i >= 0){

            i = 0;
        }
        
        console.log("Tour : " + players[i]);
        tourplayer = players[i];
        numplayer = i;
        if(i < players.length && i >= 0){

            i ++
        }
        start = 2;
       
        setTimeout(() => {msg.channel.send("**" + tourplayer + "** à toi de jouer ! Lance le dé !");}, 2000);
        des = entierAleatoire(1,6);   
    }

    //Reaction pour lancer le dé
    if(start === 2 && msg.content.includes(tourplayer)){

        msg.react("🎲");
    }


    //Placement du joueur sur le plateau
    if(start === 2 && msg.content === ("Tu as fait un " + des)){

        if(typeof plateau[numplayer] === 'undefined' || plateau[numplayer] < 0){

            plateau[numplayer] = 0;
        }
        
        console.log("Début : " + plateau[numplayer]);
        var coord = JSON.parse(fs.readFileSync('A:/Discord/plateau.json', 'utf8'));
        plateau[numplayer] =  plateau[numplayer] + des;
        console.log("Place : " + plateau[numplayer])
        var place = coord.cases[plateau[numplayer]-1];

        
        if(plateau[numplayer] === 26)
        {
            msg.channel.send("Bravo, tu es tombé sur la case 26 ! Tu as gagné !");
        }
        else if(plateau[numplayer] > 26)
        {
            msg.channel.send("Oups ! Tu as dépassé la case 26 ! Tu retournes au debut !");
            plateau[numplayer] = 0;
            start = 1;
        }

        if(place === "Alcool")
        {
            msg.channel.send("🔮**Case féerique**🔮")
            msg.channel.send(":sparkles: Woaw, une fée apparait ! :sparkles:");
            msg.channel.send("https://tenor.com/view/fairy-fairies-dog-lol-gif-5089517");
            setTimeout(() => {msg.channel.send("**C'est la fée MoiBoire ! Tu dois boire ton verre !**");}, 3000);
            setTimeout(() => {start = 1;}, 3000);
            

        }
        else if (place === "Defi")
        {
            msg.channel.send("🎯**Case Defi**🎯");
            msg.channel.send("**C'est l'heure du defi !**");
            msg.channel.send("Si tu fais un nombre plus élevée que ton dé, tu as le droit à une pause ! Sinon tu bois !");
            msg.channel.send("Lance le dé pour connaitre ton sort !");
            start = 5;

        }
        else if (place === "Pause")
        {
            msg.channel.send("⏸**Case Pause**⏸")
            msg.channel.send("Tu as le droit à une pause ! Au suivant !");
            start = 1;

        }
        else if (place === "Question")
        {
            msg.channel.send("❔**Case Question**❔")
            msg.channel.send("Tu doit répondre à 2 questions. A chaque mauvaise réponse, tu recules de 2 cases, sinon tu avances de 2 ! \nLe but : ne pas reculer plus loin de la case dont tu es parti, sinon tu bois ! ");
            setTimeout(() => {msg.channel.send(messagequestion), start = 3;}, 4000);
            score = 0;
        }

    }

    if(msg.content === "Lance le dé pour connaitre ton sort !")
    {
        msg.react("🎲");
    }

    //Envoie des questions
    if(start === 3 && e <2)
    {   
        dataquestion(entierAleatoire(0,419));
        reponses.sort();     
        msg.channel.send( question + "\n1️⃣     " + reponses[0] + "\n2️⃣     " + reponses[1] + "\n3️⃣     " + reponses[2] + "\n4️⃣     " + reponses[3]);
        start = 4
    }

    //Ajout des emoji sur les questions
    if(msg.channel.lastMessage.content.includes("4️⃣")){
        msg.react("1️⃣");
        msg.react("2️⃣");
        msg.react("3️⃣");
        msg.react("4️⃣");
    }

});

Client.on("messageReactionAdd", (rea, user) =>{

    if(!user.bot){

        //Ajout des joueurs
        if(rea.emoji.name === "✅" && rea.message.content === messageajout ){
               
            if(!players.includes(user.username))
            {
                players.push(user.username);
                console.log(players);
                if(players.length < maxplayers)
                {
                    rea.message.channel.send("Il manque " + (maxplayers - players.length) + " joueur(s)" );
                }
                
            }else{

                return;
            }          
        }

        if(rea.emoji.name === "✅" && players.length >= maxplayers){

            rea.message.channel.send("**La partie commence !**");
            rea.remove();
            start = 1;
        }

        //Lancer de dé
        if(rea.emoji.name === "🎲" && user.username === tourplayer && start === 2){
            
            rea.message.channel.send("https://tenor.com/view/dice-wind-mill-dice-dancer-dancing-cool-dice-chris-timmons-gif-13865860");
            setTimeout(() => {rea.message.channel.send("Tu as fait un " + des);}, 2000);
        }

        if(start === 5 && rea.emoji.name ===  "🎲" && user.username === tourplayer)
        {
            rea.message.channel.send("https://tenor.com/view/dice-game-roll-dice-dice-gif-16194205");
            defi = entierAleatoire(1,6);
            rea.message.channel.send("Tu as fais un : " + defi);
            if(des <= defi)
            {
                rea.message.channel.send("**Et c'est une pause !**");
                start = 1;

            }else{

                rea.message.channel.send("**Aller hop! Bois ton verre !**");
                start = 1;
            }
        }

        //Score questions
        if(user.username === tourplayer){

            if(rea.emoji.name === "1️⃣" || rea.emoji.name === "2️⃣" || rea.emoji.name === "3️⃣"  || rea.emoji.name === "4️⃣"){

                e ++;

                if(rea.emoji.name === "1️⃣"){
    
                    rep = 0;
    
                }else if (rea.emoji.name === "2️⃣"){
    
                    rep = 1;
    
                }else if (rea.emoji.name === "3️⃣"){
    
                    rep = 2;
    
                }else if (rea.emoji.name === "4️⃣"){
    
                    rep = 3;
                }
    
                if(rep >= 0 && rep <= 3){

                    if(reponses[rep] === reponse_correcte){

                        rea.message.channel.send("Réponse : " + reponse_correcte);
                        rea.message.channel.send("**Bonne Réponse !**");
                        score = score + 2;
    
                    }else{
                        
                        rea.message.channel.send("Réponse : " + reponse_correcte);
                        rea.message.channel.send("**Mauvaise Réponse !**");
                        score = score - 2;
                    }
                }    
    
                rea.message.delete();
                start = 3;
                
            }   
            
            if(e === 2){

                var res = des + score
                rea.message.channel.send("Ton score est de " + res);
                if(res < 0)
                {
                    rea.message.channel.send("**Ton score total est négatif ! Pas de chances ! Tu dois boire !**");
                }else{

                    rea.message.channel.send("**Tu as de la chance, aller avance !**");
                }
                plateau[numplayer] = plateau[numplayer] + score
                e = 0;
                start = 1;
                console.log("Place fin : "+ plateau[numplayer]);
            }    
        }
    }
});   


Client.login("ODIyMjE0MDc0NjA2NTUxMDcx.YFPAhw.BB2XMl7hIAn-jnV6R_hrK5XSHKM");
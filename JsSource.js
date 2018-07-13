
function login_in(usrName_)
{
    userInfo.usrName = usrName_
    msgView.statusText = "You are logined as " + usrName_
}

function send(data)
{
    var date = new Date()
    if(userInfo.usrName == "")
    {
        login_in(data)
        return
    }
    var msg = {
        "usrName": userInfo.usrName,
        "msgText": data,
        "msgDate": date.toLocaleString(""),
    }
    var str_msg = JSON.stringify(msg)

    history.addMessage(socket.ipAddr, "You(" + userInfo.usrName + ")")

    if(socket.ipAddr !== socket.localHost)
    {
        send(str_msg)
        if(!rContainsIp(socket.ipAddr))
        {
            msgView.listModelR.append({
                                "usrName": "Unkown",
                                "msgText": aToShort(data),
                                "ip": m_sock.ipAddr,
                                "chatId": last() === undefined ? chat + 1 : last().chatId + 1
                              })
        }
    }
    else
    {
        if(!rContainsIp(socket.ipAddr))
        {
            msgView.listModelR.append({
                                "usrName": "Local Storage",
                                "msgText": aToShort(data),
                                "ip": m_sock.ipAddr,
                                "chatId": last() === undefined ? chat + 1 : last().chatId + 1
                              })
        }
        changeChat(last() === undefined ? chat + 1 : last().chatId + 1, "127.0.0.1", "Local Storage")
    }
    add("You(" + m_sock.usrName + ")", data, date.toLocaleDateString(""))
}

function last()
{
    return msgView.listModelR.get(msgView.listModelR.count - 1)
}

function add(usrName, msgText, msgDate)
{
    if(usrName === userInfo.lastUser || usrName === "You(" + userInfo.usrName + ")")
    {
        if(usrName !== "You(" + userInfo.usrName + ")")
            msgView.usrNameText = usrName
        var el = {
            "usrName": usrName,
            "msgText": msgText,
            "msgDate": msgDate,
        }
        msgView.listModel.append(el)
    }
    for(var i = 0; i < msgView.listModelR.count; i++)
    {
        if(msgView.listModelR.get(i).ip === socket.ipAddr && msgView.listModelR.get(i).usrName !== "Local Storage")
        {
            if(usrName !== "You(" + userInfo.usrName + ")")
                msgView.listModelR.get(i).usrName = usrName
            msgView.listModelR.get(i).msgText = aToShort(msgText)
            return
        }
    }
}

function aToShort(data)
{
    var mt = "" + data
    var atext = ""
    if(mt.length > 14)
    {
        for(var j = 0; j < 8; j++)
        {
            atext += mt[j]
        }
        return atext + "..."
    }
    else
        return mt
}

function rContains(chatId)
{
    for(var j = 0; j < msgView.listModelR.count; j++)
    {
        if(msgView.listModelR.get(j).chatId === chatId)
            return true
    }
    return false
}

function rContainsIp(ipAddr)
{
    for(var j = 0; j < msgView.listModelR.count; j++)
    {
        if(msgView.listModelR.get(j).ip === ipAddr)
            return true
    }
    return false
}

function changeChat(chatId, ip, usrName)
{
    if(socket.ipAddr === ip)
        return
    chat = chatId
    socket.ipAddr = ip
    userInfo.lastUser = usrName
}

function newMessage(usrName, msgText, msgDate,ipAddress)
{
    if(userInfo.lastUser == "" || userInfo.lastUser == "Unkown")
    {
        if(last() !== undefined)
            changeChat(last().chatId,
                          last().ip,
                          last().usrName)
        userInfo.lastUser = usrName
        add(usrName, msgText, msgDate)
        for(var i = 0; i < msgView.listModelR.count; i++)
        {
            if(msgView.listModelR.get(i).chatId === chat)
            {
                msgView.listModelR.get(i).ip = ipAddress
            }
        }
    }
    else
        add(usrName, msgText, msgDate)
}


    $(document).ready(function(){
        var estadoQ = false;
        var estadoC = false;
        var estadoD = false;
        $('#btnQ').on('click', function(){
            $('.sectionToggleQ').slideToggle();
            if(estadoQ == true){
                $(this).text("¿Qué es?");
                estadoQ = false;
            }
            else{
                $(this).text("Cerrar");
                estadoQ = true;
            }
            
        });

        $('#btnC').on('click', function(){
            $('.sectionToggleC').slideToggle();
            if(estadoC == true){
                $(this).text("¿Cómo funciona?");
                estadoC = false;
            }
            else{
                $(this).text("Cerrar");
                estadoC = true;
            }
        });

        $('#btnD').on('click', function(){
            $('.sectionToggleD').slideToggle();
            if(estadoD == true){
                $(this).text("Demostración");
                estadoD = false;
            }
            else{
                $(this).text("Cerrar");
                estadoD = true;
            }
        });    
    });



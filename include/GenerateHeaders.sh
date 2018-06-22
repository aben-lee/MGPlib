# Create the gplib headers from scratch
rm -fr gplib 2> /dev/null
mkdir gplib

cd ../Aniso_Joint_Inversion
for a in `ls *.h`
do
    echo '#include "../../Aniso_Joint_Inversion/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Exceptions
for a in `ls *.h`
do
    echo '#include "../../Exceptions/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../GAClasses
for a in `ls *.h`
do
    echo '#include "../../GAClasses/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Global
for a in `ls *.h`
do
    echo '#include "../../Global/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Joint_Inversion
for a in `ls *.h`
do
    echo '#include "../../Joint_Inversion/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Neural_Network
for a in `ls *.h`
do
    echo '#include "../../Neural_Network/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Seismic_Tools
for a in `ls *.h`
do
    echo '#include "../../Seismic_Tools/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Signal_Processing
for a in `ls *.h`
do
    echo '#include "../../Signal_Processing/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Statistics
for a in `ls *.h`
do
    echo '#include "../../Statistics/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../Time_Series_Tools
for a in `ls *.h`
do
    echo '#include "../../Time_Series_Tools/'$a'"' > ../Include/gplib/`echo $a | cut -f1 -d.`
done

cd ../MT_Tools/1DMT
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/1DMT/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/3D_Model_Tools
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/3D_Model_Tools/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/EDI_Parser
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/EDI_Parser/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/J_Parser
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/J_Parser/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/MT_Tensor_Tools
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/MT_Tensor_Tools/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/ptensor
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/ptensor/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/Simple_Processing
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/Simple_Processing/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/Station_Parser
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/Station_Parser/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/Time_Series_Noise_Removal
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/Time_Series_Noise_Removal/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..

cd ../MT_Tools/Time_Series_Tools
for a in `ls *.h`
do
    echo '#include "../../MT_Tools/Time_Series_Tools/'$a'"' > ../../Include/gplib/`echo $a | cut -f1 -d.`
done
cd ..
cd ../Include/gplib
rm -fr *_p
cd ..
